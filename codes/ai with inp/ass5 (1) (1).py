import re

knowledge_base = []


def add_fact(sentence):

    # Pattern:
    # aditya is friend of akhand

    pattern = r"(\w+)\s+is\s+(\w+)\s+of\s+(\w+)"

    match = re.match(pattern, sentence.lower())

    if match:

        subject = match.group(1)
        relation = match.group(2)
        obj = match.group(3)

        knowledge_base.append((subject, relation, obj))
        if relation == "friend":
            knowledge_base.append((obj, relation, subject))

        print("Fact added successfully.\n")

    else:
        print("Invalid fact format.\n")

def who_query(sentence):

    # Pattern:
    # who is friend of aditya

    pattern = r"who\s+is\s+(\w+)\s+of\s+(\w+)"

    match = re.match(pattern, sentence.lower())

    if match:
        relation = match.group(1)
        subject = match.group(2)
        found = False
        for fact in knowledge_base:
            if fact[0] == subject and fact[1] == relation:
                print(fact[2])
                found = True
        if not found:
            print("No result found.")

    else:
        print("Invalid question format.")


# ================= YES/NO QUERY =================
def yes_no_query(sentence):
    pattern = r"is\s+(\w+)\s+(\w+)\s+of\s+(\w+)"
    match = re.match(pattern, sentence.lower())
    if match:
        subject = match.group(1)
        relation = match.group(2)
        obj = match.group(3)

        if (subject, relation, obj) in knowledge_base:
            print("YES")

        else:
            print("NO")

    else:
        print("Invalid question format.")


# ================= SHOW FACTS =================
def show_facts():

    print("\nKnowledge Base:\n")

    for fact in knowledge_base:

        print(f"{fact[0]} is {fact[1]} of {fact[2]}")


# ================= MAIN CHATBOT =================
def chatbot():

    print("===== SIMPLE AI CHATBOT =====")

    while True:

        print("\n1. Add Fact")
        print("2. Ask WHO Question")
        print("3. Ask YES/NO Question")
        print("4. Show Knowledge Base")
        print("5. Exit")

        choice = input("Enter choice: ")

        # ---------- ADD FACT ----------
        if choice == "1":
            sentence = input("\nEnter fact: ")

            add_fact(sentence)

        # ---------- WHO QUERY ----------
        elif choice == "2":
            sentence = input("\nAsk question: ")

            who_query(sentence)

        # ---------- YES/NO QUERY ----------
        elif choice == "3":

            sentence = input("\nAsk question: ")

            yes_no_query(sentence)

        # ---------- SHOW FACTS ----------
        elif choice == "4":
            show_facts()

        # ---------- EXIT ----------
        elif choice == "5":
            print("Exiting chatbot...")
            break

        else:
            print("Invalid choice.")
# ================= RUN =================
chatbot()


# import re

# # ================= KNOWLEDGE BASE =================
# products = {
#     "laptop": {
#         "price": "50000",
#         "brand": "lenovo",
#         "stock": "available"
#     },

#     "phone": {
#         "price": "25000",
#         "brand": "samsung",
#         "stock": "available"
#     },

#     "headphones": {
#         "price": "3000",
#         "brand": "boat",
#         "stock": "outofstock"
#     }
# }

# # ================= SHOW PRODUCTS =================
# def show_products():

#     print("\nAvailable Products:\n")

#     for product in products:

#         print(product)


# # ================= PRICE QUERY =================
# def price_query(sentence):

#     # what is price of laptop

#     pattern = r"what\s+is\s+price\s+of\s+(\w+)"

#     match = re.match(pattern, sentence.lower())

#     if match:

#         product = match.group(1)

#         if product in products:

#             print("Price =", products[product]["price"])

#         else:

#             print("Product not found.")

#     else:

#         print("Invalid question format.")


# # ================= BRAND QUERY =================
# def brand_query(sentence):

#     # what is brand of laptop

#     pattern = r"what\s+is\s+brand\s+of\s+(\w+)"

#     match = re.match(pattern, sentence.lower())

#     if match:

#         product = match.group(1)

#         if product in products:

#             print("Brand =", products[product]["brand"])

#         else:

#             print("Product not found.")

#     else:

#         print("Invalid question format.")


# # ================= STOCK QUERY =================
# def stock_query(sentence):

#     # is laptop available

#     pattern = r"is\s+(\w+)\s+available"

#     match = re.match(pattern, sentence.lower())

#     if match:

#         product = match.group(1)

#         if product in products:

#             if products[product]["stock"] == "available":

#                 print("YES, product is available.")

#             else:

#                 print("NO, product is out of stock.")

#         else:

#             print("Product not found.")

#     else:

#         print("Invalid question format.")


# # ================= ADD PRODUCT =================
# def add_product():

#     name = input("Enter product name: ").lower()

#     price = input("Enter price: ")

#     brand = input("Enter brand: ").lower()

#     stock = input("Enter stock status (available/outofstock): ").lower()

#     products[name] = {
#         "price": price,
#         "brand": brand,
#         "stock": stock
#     }

#     print("Product added successfully.")


# # ================= MAIN CHATBOT =================
# def chatbot():

#     print("===== CUSTOMER SUPPORT CHATBOT =====")

#     while True:

#         print("\n1. Show Products")
#         print("2. Ask Product Price")
#         print("3. Ask Product Brand")
#         print("4. Check Availability")
#         print("5. Add Product")
#         print("6. Exit")

#         choice = input("Enter choice: ")

#         # ---------- SHOW ----------
#         if choice == "1":

#             show_products()

#         # ---------- PRICE ----------
#         elif choice == "2":

#             print("\nExample:")
#             print("what is price of laptop")

#             sentence = input("\nAsk question: ")

#             price_query(sentence)

#         # ---------- BRAND ----------
#         elif choice == "3":

#             print("\nExample:")
#             print("what is brand of phone")

#             sentence = input("\nAsk question: ")

#             brand_query(sentence)

#         # ---------- STOCK ----------
#         elif choice == "4":

#             print("\nExample:")
#             print("is laptop available")

#             sentence = input("\nAsk question: ")

#             stock_query(sentence)

#         # ---------- ADD PRODUCT ----------
#         elif choice == "5":

#             add_product()

#         # ---------- EXIT ----------
#         elif choice == "6":

#             print("Exiting chatbot...")
#             break

#         else:

#             print("Invalid choice.")


# # ================= RUN =================
# chatbot()