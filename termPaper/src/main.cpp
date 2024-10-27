using namespace std;

#include <iostream>
#include <array>
#include <string.h>

typedef struct Node
{
    int coefficient;
    int power;
    Node *next;
} Node;

array<string, 3> readPolynomial()
{
    string input = "";

    cout << "Enter input: ";
    cin >> input;

    cout << "Input: " << input << endl;

    int start = 0;
    int countArgs = 0;
    array<string, 3> arr = {};

    for (size_t i = 0; i < input.length(); i++)
    {
        char ch = input.at(i);

        if (ch == '-' && i > 0)
        {
            arr[countArgs] = input.substr(start, i - start);
            // cout << "START: " << start << " End: " << i << " ARGS: " << countArgs << endl;
            // cout << "ARGS: " << input.substr(start, i - start) << endl;
            start = i;
            countArgs++;
        }

        if (ch == '+')
        {
            arr[countArgs] = input.substr(start, i - start);
            // cout << "START: " << start << " End: " << i << " ARGS: " << countArgs << endl;
            // cout << "ARGS: " << input.substr(start, i - start) << endl;
            start = i + 1;
            countArgs++;
        }

        if (i == input.length() - 1)
        {
            // cout << "START: " << start << " End: " << input.length() - 1 << " ARGS: " << countArgs << endl;
            arr[countArgs] = input.substr(start, input.length() - start);
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
    array<string, 3> polynomal = readPolynomial();

    for (size_t i = 0; i < 3; i++)
    {
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
            if (curr->power == 2)
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
                if (curr->power == 2)
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
                if (curr->power == 2)
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

void convertPolynomialToFull(Node *&head)
{
    bool arr[3] = {false, false, false};

    Node *curr = head;

    if (head->next != NULL)
    {
        while (curr != NULL)
        {
            arr[curr->power] = true;
            curr = curr->next;
        }
    }
    else
    {
        arr[head->power] = true;
    }

    // arg 0 is x^0, arg 1 is x^1, arg 2 is x^2
    int missingArg = 0;

    for (int i = 2; i >= 0; i--)
    {
        if (arr[i] == false)
        {
            if (i == 2)
            {
                Node *newNode = new Node{};
                newNode->coefficient = 0;
                newNode->power = 2;

                newNode->next = head;
                head = newNode;
            }

            if (i == 1)
            {
                Node *newNode = new Node{};
                newNode->coefficient = 0;
                newNode->power = 1;

                newNode->next = head->next;
                head->next = newNode;
            }

            if (i == 0)
            {
                Node *newNode = new Node{};
                newNode->coefficient = 0;
                newNode->power = 0;

                head->next->next = newNode;
            }
        }
    }
}

int main()
{
    Node *poly1 = createLinkedList();

    cout << endl
         << "TRAVERSE BEFORE CONVERT" << endl;
    traverseLinkedList(poly1);
    getPolynomial(poly1);

    convertPolynomialToFull(poly1);

    cout << endl
         << "TRAVERSE AFTER CONVERT" << endl;
    traverseLinkedList(poly1);

    getPolynomial(poly1);

    return 0;
}
