using namespace std;

#include <iostream>
#include <array>
#include <string.h>
#include <vector>

typedef struct Node
{
    int coefficient;
    int power;
    Node *next;
} Node;

vector<string> readPolynomial()
{
    string input = "";

    cout << "Enter input: ";
    cin >> input;

    cout << "Input: " << input << endl;

    int start = 0;
    int countArgs = 0;
    vector<string> arr = {};

    for (size_t i = 0; i < input.length(); i++)
    {
        char ch = input.at(i);

        if (ch == '-' && i > 0)
        {
            string substr = input.substr(start, i - start);
            arr.push_back(substr);
            // cout << "START: " << start << " End: " << i << " ARGS: " << countArgs << endl;
            // cout << "ARGS: " << input.substr(start, i - start) << endl;
            start = i;
            countArgs++;
        }

        if (ch == '+')
        {
            string substr = input.substr(start, i - start);
            arr.push_back(substr);
            // cout << "START: " << start << " End: " << i << " ARGS: " << countArgs << endl;
            // cout << "ARGS: " << input.substr(start, i - start) << endl;
            start = i + 1;
            countArgs++;
        }

        if (i == input.length() - 1)
        {
            // cout << "START: " << start << " End: " << input.length() - 1 << " ARGS: " << countArgs << endl;
            string substr = input.substr(start, input.length() - start);
            arr.push_back(substr);
        }
    }

    return arr;
}

Node *createNode(string input)
{
    int coefficient = 0;
    int power = 0;

    size_t x_pos = input.find('x');
    if (x_pos != std::string::npos)
    {
        string coef_str = input.substr(0, x_pos);

        if (!coef_str.empty())
        {
            coefficient = stoi(coef_str);
        }

        size_t power_pos = input.find('^', x_pos);
        if (power_pos != string::npos)
        {
            string power_str = input.substr(power_pos + 1);
            if (!power_str.empty())
            {
                power = stoi(power_str);
            }
        }
        else
        {
            power = 1;
        }
    }
    else
    {
        // If 'x' is not found, assume it's a constant term
        coefficient = std::stoi(input);
        power = 0;
    }

    Node *n = new Node{};
    n->coefficient = coefficient;
    n->power = power;
    n->next = NULL;

    return n;
}

void printNode(Node *n)
{
    cout << "Coefficient: " << n->coefficient << " Power: " << n->power << endl;
}

void appendToLinkedList(Node *h, Node *n)
{
    Node *curr = h;

    while (curr->next != NULL)
    {
        curr = curr->next;
    }

    curr->next = n;
}

Node *createLinkedList()
{
    Node *head = NULL;
    vector<string> polynomal = readPolynomial();

    for (size_t i = 0; i < polynomal.size(); i++)
    {
        // cout << polynomal[i] << endl;

        if (!polynomal[i].empty())
        {
            Node *newNode = createNode(polynomal[i]);

            if (head == NULL)
            {
                head = newNode;
            }
            else
            {
                appendToLinkedList(head, newNode);
            }
        }
    }

    return head;
}

void sortNodesByPower(Node *head)
{
    if (head == NULL || head->next == NULL)
    {
        return; // List is empty or has only one node
    }

    Node *current;
    Node *nextNode;
    int swapped;

    do
    {
        swapped = 0;
        current = head;

        while (current->next != NULL)
        {
            nextNode = current->next;

            if (current->power < nextNode->power)
            {
                // Swap coefficients and powers
                int tempCoeff = current->coefficient;
                int tempPower = current->power;
                current->coefficient = nextNode->coefficient;
                current->power = nextNode->power;
                nextNode->coefficient = tempCoeff;
                nextNode->power = tempPower;

                swapped = 1;
            }
            current = current->next;
        }
    } while (swapped);
}

void traverseLinkedList(Node *head)
{
    Node *curr = head;

    while (curr != NULL)
    {
        printNode(curr);
        curr = curr->next;
    }
}

void getPolynomial(Node *head)
{
    Node *curr = head;
    int count = 0;

    while (curr != NULL)
    {
        if (count == 0)
        {
            if (curr->power >= 2)
            {
                cout << curr->coefficient << "x^" << curr->power;
            }

            if (curr->power == 1)
            {
                cout << curr->coefficient << "x";
            }

            if (curr->power == 0)
            {
                cout << curr->coefficient;
            }
        }
        else
        {
            if (curr->coefficient >= 0)
            {
                if (curr->power >= 2)
                {
                    cout << "+" << curr->coefficient << "x^" << curr->power;
                }

                if (curr->power == 1)
                {
                    cout << "+" << curr->coefficient << "x";
                }

                if (curr->power == 0)
                {
                    cout << "+" << curr->coefficient;
                }
            }
            else
            {
                if (curr->power >= 2)
                {
                    cout << curr->coefficient << "x^" << curr->power;
                }

                if (curr->power == 1)
                {
                    cout << curr->coefficient << "x";
                }

                if (curr->power == 0)
                {
                    cout << curr->coefficient;
                }
            }
        }

        curr = curr->next;
        count++;
    }
    cout << endl;
}

void convertPolynomialToFull(Node *head)
{
    Node *curr = head;

    while (curr != NULL)
    {
        if (curr->next != NULL)
        {
            int diffPower = curr->power - curr->next->power;

            for (int i = 0; i < diffPower - 1; i++)
            {
                Node *newNode = new Node{};

                newNode->coefficient = 0;
                newNode->power = curr->power - 1;
                newNode->next = curr->next;

                curr->next = newNode;
                curr = newNode;
            }
        }
        else
        {
            while (curr->power != 0)
            {
                Node *newNode = new Node{};

                newNode->coefficient = 0;
                newNode->power = curr->power - 1;
                newNode->next = curr->next;

                curr->next = newNode;
                curr = newNode;
            }
        }

        curr = curr->next;
    }
}

int main()
{
    Node *poly1 = createLinkedList();

    sortNodesByPower(poly1);
    convertPolynomialToFull(poly1);

    cout << endl
         << "TRAVERSE AFTER CONVERT" << endl;
    traverseLinkedList(poly1);
    getPolynomial(poly1);

    return 0;
}
