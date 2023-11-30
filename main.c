#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define MAX_CART_ITEMS 10
#define TAX 0.13
#define SHIPPING 5.99

// Structure to represent a product
struct Product {
    int id;
    char name[50];
    char category[20];
    float price;
    int quantity;
};

// Structure to represent an item in the shopping cart
struct CartItem {
    struct Product product;
    int quantity;
};

// Function prototypes
void displayMenu();
void addProduct(struct Product products[], int *count);
void updateProduct(struct Product products[], int count);
void removeProduct(struct Product products[], int *count);
void displayProducts(struct Product products[], int count);
int findProductById(struct Product products[], int count, int productId);
void addToCart(struct Product products[], int productCount, struct CartItem cart[], int* cartItemCount);
void removeFromCart(struct CartItem cart[], int* cartItemCount);
void displayCart(struct CartItem cart[], int cartItemCount);
void generateBill(struct CartItem cart[], int cartItemCount);

// The entry point of the program
int main() {
  struct Product inventory[MAX_PRODUCTS];
  struct CartItem shoppingCart[MAX_CART_ITEMS];
  int cartItemCount = 0, productCount = 0, choice;

  do {
    displayMenu();
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
      case 1:
        displayProducts(inventory, productCount);
        break;
      case 2:
        addProduct(inventory, &productCount);
        break;
      case 3:
        updateProduct(inventory, productCount);
        break;
      case 4:
        removeProduct(inventory, &productCount);
        break;
      case 5:
        addToCart(inventory, productCount, shoppingCart, &cartItemCount);
        break;
      case 6:
        removeFromCart(shoppingCart, &cartItemCount);
        break;
      case 7:
        displayCart(shoppingCart, cartItemCount);
        break;
      case 8:
        generateBill(shoppingCart, cartItemCount);
        break;
      case 9:
        printf("\n------------------------------------------------------------\n");
        printf("Exiting the program. Thank you for shopping!\n");
        printf("------------------------------------------------------------\n");
        break;
      default:
        printf("\n------------------------------------------------------------\n");
        printf("Invalid choice. Please try again.\n");
        printf("------------------------------------------------------------\n");
    }

  } while (choice != 9);

  return 0;
}

/// Displays the menu to select an option
void displayMenu() {
  printf("\n=== Online Shopping System ===\n");
  printf("1. Display Products\n");
  printf("2. Add Product\n");
  printf("3. Update Product\n");
  printf("4. Remove Product\n");
  printf("5. Add to Cart\n");
  printf("6. Remove from Cart\n");
  printf("7. View Cart\n");
  printf("8. Generate Bill\n");
  printf("9. Exit\n");
}

/// Displays the list of products
void displayProducts(struct Product products[], int count) {
  if(count > 0) {
    printf("\n=== Product List ===\n");
    printf("%-4s %-20s %-15s %-10s %s\n", "ID", "Name", "Category", "Price", "Quantity");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
      printf("%-4d %-20s %-15s $%-9.2f %d\n", products[i].id, products[i].name, products[i].category, products[i].price, products[i].quantity);
    }
  } else {
    printf("\n------------------------------------------------------------\n");
    printf("No products to display.\n");
    printf("------------------------------------------------------------\n");
  }
}

/// Asks the user to enter the details of a new product and adds it to the inventory.
void addProduct(struct Product products[], int *count) {
  if (*count < 100) {
    printf("\n=== Add Product ===\n");

    products[*count].id = *count + 1; // Auto-increment product ID
    printf("Name: ");
    scanf("%s", products[*count].name);

    printf("Category: ");
    scanf("%s", products[*count].category);

    printf("Price: $");
    scanf("%f", &products[*count].price);

    printf("Quantity: ");
    scanf("%d", &products[*count].quantity);

    (*count)++;
    printf("\n------------------------------------------------------------\n");
    printf("Product added successfully!\n");
    printf("------------------------------------------------------------\n");
  } else {
    printf("\n------------------------------------------------------------\n");
    printf("Cannot add more products. Maximum limit reached.\n");
    printf("------------------------------------------------------------\n");
  }
}

/// Asks the user to enter the ID of the product to be updated and updates the product details.
void updateProduct(struct Product products[], int count) {
  int productId, index;

  printf("\n=== Update Product ===\n");
  displayProducts(products, count);

  if (count > 0) {
    printf("Enter the ID of the product you want to update: ");
    scanf("%d", &productId);

    for (index = 0; index < count; index++) {
      if (products[index].id == productId) {
        printf("Enter updated details for product %d:\n", productId);

        printf("Name: ");
        scanf("%s", products[index].name);

        printf("Category: ");
        scanf("%s", products[index].category);

        printf("Price: $");
        scanf("%f", &products[index].price);

        printf("Quantity: ");
        scanf("%d", &products[index].quantity);

        printf("\n------------------------------------------------------------\n");
        printf("Product updated successfully!\n");
        printf("------------------------------------------------------------\n");
        break;
      }
    }

    if (index == count) {
      printf("\n------------------------------------------------------------\n");
      printf("Product with ID %d not found.\n", productId);
      printf("------------------------------------------------------------\n");
    }
  } else {
    printf("\n------------------------------------------------------------\n");
    printf("No products available for update.\n");
    printf("------------------------------------------------------------\n");
  }
}

/// Asks the user to enter the ID of the product to be removed and removes the product from the inventory.
void removeProduct(struct Product products[], int *count) {
  int productId, index;

  printf("\n=== Remove Product ===\n");
  displayProducts(products, *count);

  if (*count > 0) {
    printf("Enter the ID of the product you want to remove: ");
    scanf("%d", &productId);

    for (index = 0; index < *count; index++) {
      if (products[index].id == productId) {
          // Remove the product from the list
          for (int i = index; i < *count - 1; i++) {
              products[i] = products[i + 1];
          }

          (*count)--;
          printf("\n------------------------------------------------------------\n");
          printf("Product with ID %d removed successfully!\n", productId);
          printf("------------------------------------------------------------\n");
          break;
      }
    }

    if (index == *count) {
      printf("\n------------------------------------------------------------\n");
      printf("Product with ID %d not found.\n", productId);
      printf("------------------------------------------------------------\n");
    }
  } else {
    printf("\n------------------------------------------------------------\n");
    printf("No products available for removal.\n");
    printf("------------------------------------------------------------\n");
  }
}

/// Finds the product with the given ID in the inventory and returns its index
int findProductById(struct Product products[], int count, int productId) {
  for (int i = 0; i < count; i++) {
    if (products[i].id == productId) {
        return i; // Return the index of the product in the array
    }
  }
  return -1; // Product not found
}

/// Asks the user to enter the ID of the product to be added to the cart and adds the product to the cart.
void addToCart(struct Product products[], int productCount, struct CartItem cart[], int* cartItemCount) {
  int productId, quantity;

  displayProducts(products, productCount);

  printf("Enter the product ID you want to add to the cart: ");
  scanf("%d", &productId);

  int productIndex = findProductById(products, productCount, productId);

  if (productIndex != -1) {
    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    if (quantity > 0 && quantity <= products[productIndex].quantity) {
      // Add the product to the cart
      cart[*cartItemCount].product = products[productIndex];
      cart[*cartItemCount].quantity = quantity;
      (*cartItemCount)++;

      // Update the product quantity in the inventory
      products[productIndex].quantity -= quantity;

      printf("\n------------------------------------------------------------\n");
      printf("Product added to the cart successfully!\n");
      printf("------------------------------------------------------------\n");
    } else {
      printf("\n------------------------------------------------------------\n");
      printf("Invalid quantity or insufficient stock.\n");
      printf("------------------------------------------------------------\n");
    }
  } else {
    printf("\n------------------------------------------------------------\n");
    printf("Product not found.\n");
    printf("------------------------------------------------------------\n");
  }
}

/// Asks the user to enter the index of the item to be removed from the cart and removes the item from the cart.
void removeFromCart(struct CartItem cart[], int* cartItemCount) {
  int cartIndex, quantity;

  displayCart(cart, *cartItemCount);

  if (*cartItemCount > 0) {
    printf("Enter the index of the item you want to remove: ");
    scanf("%d", &cartIndex);

    if (cartIndex >= 0 && cartIndex < *cartItemCount) {
      // Update the product quantity in the inventory
      cart[cartIndex].product.quantity += cart[cartIndex].quantity;

      // Remove the item from the cart
      for (int i = cartIndex; i < *cartItemCount - 1; i++) {
          cart[i] = cart[i + 1];
      }

      (*cartItemCount)--;

      printf("\n------------------------------------------------------------\n");
      printf("Item removed from the cart successfully!\n");
      printf("------------------------------------------------------------\n");
    } else {
      printf("\n------------------------------------------------------------\n");
      printf("Invalid index.\n");
      printf("------------------------------------------------------------\n");
    }
  } else {
    printf("\n------------------------------------------------------------\n");
    printf("The cart is empty.\n");
    printf("------------------------------------------------------------\n");
  }
}

/// Displays the items in the cart.
void displayCart(struct CartItem cart[], int cartItemCount) {
  if (cartItemCount > 0) {
    printf("\n=== Shopping Cart ===\n");
    printf("%-4s %-20s %-15s %-10s %s\n", "ID", "Name", "Category", "Price", "Quantity");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < cartItemCount; i++) {
      printf("%-4d %-20s %-15s $%-9.2f %d\n",
      cart[i].product.id, cart[i].product.name, cart[i].product.category, cart[i].product.price, cart[i].quantity);
    }
  } else {
    printf("\n------------------------------------------------------------\n");
    printf("The cart is empty.\n");
    printf("------------------------------------------------------------\n");
  }
}

/// Displays the bill for the items in the cart.
void generateBill(struct CartItem cart[], int cartItemCount) {
  float total = 0.0, itemTotal, tax;
  if (cartItemCount > 0) {

    printf("\n=== Bill ===\n");
    printf("%-4s %-20s %-15s %-10s %-10s %s\n", "ID", "Name", "Category", "Price", "Tax", "Quantity");
    printf("-----------------------------------------------------------------------------\n");

    for (int i = 0; i < cartItemCount; i++) {
      tax = cart[i].product.price * TAX;
      itemTotal = (cart[i].product.price + tax) * cart[i].quantity + SHIPPING;
      total += itemTotal;

      printf("%-4d %-20s %-15s $%-9.2f $%-9.2f %d\n",
      cart[i].product.id, cart[i].product.name, cart[i].product.category, cart[i].product.price, tax, cart[i].quantity );
    }

    printf("-----------------------------------------------------------------------------\n");
    printf("%-60s $%-9.2f\n", "Shipping:", SHIPPING);
    printf("%-60s $%-9.2f\n", "Total:", total);
  } else {
    printf("\n------------------------------------------------------------\n");
    printf("The cart is empty. Add items to the cart before generating the bill.\n");
    printf("------------------------------------------------------------\n");
  }
}

