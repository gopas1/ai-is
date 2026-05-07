# =========================================================
# FIRST ORDER LOGIC BASED TRAVEL RECOMMENDATION CHATBOT
# =========================================================

# Run Command:
# python "Pasted code(4).py"

# ---------------------------------------------------------
# IMPORTING REQUIRED LIBRARIES
# ---------------------------------------------------------

import re                  # Used for pattern matching in user text
import tkinter as tk      # Used for creating GUI window

# Constant user name used inside knowledge base
USER = "user"


# =========================================================
# FIRST ORDER LOGIC ENGINE
# =========================================================

# Atom class represents logical facts like:
# climate(user, warm)
# activity(user, relaxing)

class Atom:
    def __init__(self, predicate, *args):
        self.predicate = predicate
        self.args = tuple(args)

    # Enables Atom objects to be stored in dictionaries/sets
    def __hash__(self):
        return hash((self.predicate, self.args))

    # Checks equality between two Atom objects
    def __eq__(self, other):
        return (
            isinstance(other, Atom)
            and self.predicate == other.predicate
            and self.args == other.args
        )

    # String representation of facts
    def __repr__(self):
        return f"{self.predicate}({', '.join(self.args)})"

    # Replaces variables with actual values
    def substitute(self, bindings):
        return Atom(
            self.predicate,
            *[resolve_term(arg, bindings) for arg in self.args],
        )


# Rule class stores logical implication rules
# Example:
# IF climate is warm AND activity is relaxing
# THEN recommend bali

class Rule:
    def __init__(self, name, head, body):
        self.name = name
        self.head = head
        self.body = body


# Checks whether a term is a variable
# Variables start with '?'
def is_variable(term):
    return isinstance(term, str) and term.startswith("?")


# Resolves variable bindings
def resolve_term(term, bindings):
    while is_variable(term) and term in bindings:
        term = bindings[term]
    return term


# Unification algorithm
# Matches user facts with rule patterns
def unify(pattern, fact, bindings=None):

    # Predicate and argument count must match
    if pattern.predicate != fact.predicate or len(pattern.args) != len(fact.args):
        return None

    current = dict(bindings or {})

    # Compare arguments one by one
    for left, right in zip(pattern.args, fact.args):

        left = resolve_term(left, current)
        right = resolve_term(right, current)

        # Variable binding
        if is_variable(left):
            current[left] = right

        elif is_variable(right):
            current[right] = left

        # Facts do not match
        elif left != right:
            return None

    return current


# =========================================================
# KNOWLEDGE BASE
# =========================================================

class FirstOrderLogicKB:

    def __init__(self):

        # Stores all facts
        self.facts = {}

        # Loads predefined rules
        self.rules = self._build_rules()


    # Adds new fact to knowledge base
    def add_fact(self, atom, source):

        if atom not in self.facts:
            self.facts[atom] = source
            return True

        return False


    # Creates all recommendation rules
    def _build_rules(self):

        return [

            # Warm + relaxing + low budget => Bali
            Rule(
                "budget_warm_beach",
                Atom("recommend", USER, "bali"),
                [
                    Atom("climate", USER, "warm"),
                    Atom("activity", USER, "relaxing"),
                    Atom("budget", USER, "low")
                ],
            ),

            # Warm + relaxing + high budget => Maldives
            Rule(
                "luxury_warm_beach",
                Atom("recommend", USER, "maldives"),
                [
                    Atom("climate", USER, "warm"),
                    Atom("activity", USER, "relaxing"),
                    Atom("budget", USER, "high")
                ],
            ),

            # Cold + adventure => Swiss Alps
            Rule(
                "cold_adventure",
                Atom("recommend", USER, "swiss_alps"),
                [
                    Atom("climate", USER, "cold"),
                    Atom("activity", USER, "adventure")
                ],
            ),
        ]


    # Forward chaining inference engine
    def infer(self):

        changed = True

        while changed:

            changed = False
            facts_snapshot = list(self.facts.keys())

            # Check every rule
            for rule in self.rules:

                # Solve rule body
                for bindings, support in self._solve(rule.body, facts_snapshot):

                    # Create inferred fact
                    inferred = rule.head.substitute(bindings)

                    source = f"{rule.name} using {', '.join(map(str, support))}"

                    # Add new inferred fact
                    if self.add_fact(inferred, source):
                        changed = True


    # Recursive solver
    def _solve(self, body, facts, index=0, bindings=None, support=None):

        bindings = dict(bindings or {})
        support = list(support or [])

        # All conditions satisfied
        if index >= len(body):
            yield bindings, support
            return

        goal = body[index].substitute(bindings)

        # Match goal with known facts
        for fact in facts:

            updated = unify(goal, fact, bindings)

            if updated is None:
                continue

            next_support = support + [fact]

            yield from self._solve(
                body,
                facts,
                index + 1,
                updated,
                next_support
            )


    # Query the knowledge base
    def query(self, atom):

        self.infer()

        matches = []

        for fact, source in self.facts.items():

            bindings = unify(atom, fact, {})

            if bindings is not None:
                matches.append((fact, source, bindings))

        return matches


# =========================================================
# DESTINATION DATABASE
# =========================================================

DESTINATION_DETAILS = {

    "bali":
    "Bali, Indonesia - Beautiful beaches and affordable villas.",

    "maldives":
    "The Maldives - Luxury overwater resorts.",

    "swiss_alps":
    "Swiss Alps - Snowy mountain adventures."
}


# =========================================================
# TEXT PROCESSING FUNCTIONS
# =========================================================

# Converts text to lowercase
def normalize(text):
    return text.strip().lower()


# Detects climate preference
def detect_climate(text):

    if any(keyword in text for keyword in
           ["warm", "hot", "sunny", "beach"]):
        return "warm"

    if any(keyword in text for keyword in
           ["cold", "snow", "winter"]):
        return "cold"

    return None


# Detects activity preference
def detect_activity(text):

    if any(keyword in text for keyword in
           ["relax", "spa", "chill"]):
        return "relaxing"

    if any(keyword in text for keyword in
           ["adventure", "hiking", "ski"]):
        return "adventure"

    return None


# Detects budget preference
def detect_budget(text):

    if any(keyword in text for keyword in
           ["cheap", "budget", "affordable"]):
        return "low"

    if any(keyword in text for keyword in
           ["luxury", "expensive"]):
        return "high"

    return None


# =========================================================
# CHATBOT CLASS
# =========================================================

class TravelLogicBot:

    def __init__(self):

        # Create knowledge base
        self.kb = FirstOrderLogicKB()

        # Add default user fact
        self.kb.add_fact(Atom("person", USER), "system")


    # Stores user preferences
    def _ingest_user_input(self, text):

        normalized = normalize(text)

        climate = detect_climate(normalized)
        activity = detect_activity(normalized)
        budget = detect_budget(normalized)

        # Add facts into knowledge base
        if climate:
            self.kb.add_fact(
                Atom("climate", USER, climate),
                "user"
            )

        if activity:
            self.kb.add_fact(
                Atom("activity", USER, activity),
                "user"
            )

        if budget:
            self.kb.add_fact(
                Atom("budget", USER, budget),
                "user"
            )


    # Generates recommendation
    def _recommendation_response(self):

        query = Atom("recommend", USER, "?destination")

        results = self.kb.query(query)

        if not results:
            return "No destination matched."

        response = []

        for fact, source, _ in results:

            dest = fact.args[1]

            response.append(
                DESTINATION_DETAILS.get(dest, dest)
            )

        return "\n".join(response)


    # Main chatbot response function
    def respond(self, user_input):

        self._ingest_user_input(user_input)

        return self._recommendation_response()


# =========================================================
# GUI SECTION
# =========================================================

# Create chatbot object
bot = TravelLogicBot()


# Send message function
def send_msg():

    user_input = input_box.get()

    if user_input.strip() == "":
        return

    # Display user message
    chat_area.config(state=tk.NORMAL)

    chat_area.insert(
        tk.END,
        "You: " + user_input + "\n"
    )

    # Get bot reply
    response = bot.respond(user_input)

    # Display bot response
    chat_area.insert(
        tk.END,
        "TravelBot: " + response + "\n\n"
    )

    # Clear input field
    input_box.delete(0, tk.END)

    chat_area.see(tk.END)

    chat_area.config(state=tk.DISABLED)


# =========================================================
# TKINTER WINDOW CREATION
# =========================================================

window = tk.Tk()

window.title("Logic Travel Agent")

window.geometry("600x550")


# Chat display area
chat_area = tk.Text(
    window,
    bg="#1a2530",
    fg="#e0e0e0",
    font=("Helvetica", 11),
    wrap=tk.WORD
)

chat_area.pack(
    padx=10,
    pady=10,
    fill=tk.BOTH,
    expand=True
)

chat_area.config(state=tk.DISABLED)


# Bottom input section
bottom_frame = tk.Frame(window)

bottom_frame.pack(fill=tk.X, padx=10, pady=(0,10))


# User input field
input_box = tk.Entry(
    bottom_frame,
    width=35,
    font=("Helvetica", 12)
)

input_box.pack(side=tk.LEFT, fill=tk.X, expand=True)


# Enter key binding
input_box.bind("<Return>", lambda event: send_msg())


# Send button
send_button = tk.Button(
    bottom_frame,
    text="Send",
    command=send_msg,
    bg="#2b8cbe",
    fg="white",
    font=("Helvetica", 11, "bold")
)

send_button.pack(side=tk.LEFT, padx=(10, 0))


# Welcome message
chat_area.config(state=tk.NORMAL)

chat_area.insert(
    tk.END,
    "TravelBot: Welcome! Tell me your travel preferences.\n\n"
)

chat_area.config(state=tk.DISABLED)


# Start GUI loop
window.mainloop()