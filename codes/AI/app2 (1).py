import re

orders = {
    "1001": {"status": "shipped", "customer": "rahul"},
    "1002": {"status": "processing", "customer": "anita"},
    "1003": {"status": "delivered", "customer": "vikram"},
}

products = {
    "laptop": {"stock": True},
    "mouse": {"stock": False},
    "keyboard": {"stock": True},
}


def can_answer_order_status(order_id):
    return order_id in orders


def is_product_available(product):
    return product in products and products[product]["stock"]


def is_product_unavailable(product):
    return product in products and not products[product]["stock"]



def extract_order_id(text):
    match = re.search(r"\b\d{4}\b", text)
    return match.group() if match else None


def extract_product(text):
    for product in products:
        if product in text:
            return product
    return None


def generate_response(user_input):
    text = user_input.lower().strip()
    responses = []

    # Greeting intent
    if any(word in text for word in ["hi", "hello", "hey"]):
        return "Hello. How can I assist you with your order or product query?"
    
    if " and " in text or "," in text:
        parts = re.split(r"\band\b|,", text)
        for part in parts:
            part = part.strip()
            if part:
                result = generate_response(part)
                if result and result not in responses:
                    responses.append(result)
        if responses:
            return " | ".join(responses)

    # Return request intent
    if "return" in text:
        context["last_return_query"] = True
        order_id = extract_order_id(text)

        if order_id and can_answer_order_status(order_id):
            return f"Return request for order {order_id} has been noted. Our support team will guide you further."

        return "Please provide your order ID for the return request."


    order_id = extract_order_id(text)
    if order_id:
        if context.get("last_return_query"):
            context["last_return_query"] = False
            if can_answer_order_status(order_id):
                return f"Return request for order {order_id} has been noted. Our support team will guide you further."
            return "I could not find that order in the system."

        if context.get("last_order_query"):
            context["last_order_query"] = False
            if can_answer_order_status(order_id):
                status = orders[order_id]["status"]
                return f"Order {order_id} is currently {status}."
            return "I could not find that order in the system."

    # Order status reasoning
    if "order" in text or "status" in text or "track" in text:
        context["last_order_query"] = True
        order_id = extract_order_id(text)

        if not order_id:
            return "Please provide your order ID."

        if can_answer_order_status(order_id):
            context["last_order_query"] = False
            status = orders[order_id]["status"]
            return f"Order {order_id} is currently {status}."
        else:
            return "I could not find that order in the system."

    # Product availability reasoning
    if "available" in text or "stock" in text or "have" in text:
        product = extract_product(text)

        if not product:
            return "Please mention the product name."

        if is_product_available(product):
            return f"Yes, {product} is available in stock."

        if is_product_unavailable(product):
            return f"Sorry, {product} is currently out of stock."

        return "I do not have information about that product."

    # Fallback
    return "I can help with order tracking, returns, and product availability."


context = {
    "last_intent": None,
    "last_order_query": False,
    "last_return_query": False,
}


#loop
def chatbot():
    print("Customer Support Chatbot (type 'exit' to stop)")

    while True:
        user_input = input("You: ")

        if user_input.lower() == "exit":
            print("Bot: Thank you for contacting support.")
            break

        response = generate_response(user_input)
        print("Bot:", response)


if __name__ == "__main__":
    chatbot()
