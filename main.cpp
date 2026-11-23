import std;

template <typename T>
struct Node {
    T data;
    Node* next;

    Node(const T& value, Node* next_node = nullptr) : data(value), next(next_node) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* head_;
    std::size_t size_;
public:
    LinkedList() : head_(nullptr), size_(0) {}

    LinkedList(const LinkedList& other) : head_(nullptr), size_(0) {
        Node<T>* current = other.head_;
        while (current) {
            push_tail(current->data);
            current = current->next;
        }
    }

    LinkedList(std::size_t count, T min_val, T max_val, unsigned int seed = 0) : head_(nullptr), size_(0) {
        if (min_val > max_val) {
            throw std::invalid_argument("Minimum value cannot be greater than maximum value");
        }
        if (seed == 0) {
            seed = static_cast<unsigned int>(std::time(nullptr));
        }
        std::mt19937 generator(seed);
        std::uniform_int_distribution<long long> distribution(static_cast<long long>(min_val), static_cast<long long>(max_val));

        for (std::size_t i = 0; i < count; ++i) {
            push_tail(static_cast<T>(distribution(generator)));
        }
    }

    ~LinkedList() {
        while (head_) {
            pop_head();
        }
    }

    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            while (head_) {
                pop_head();
            }
            Node<T>* current = other.head_;
            while (current) {
                push_tail(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    std::size_t get_size() const {
        return size_;
    }

    void push_head(const T& value) {
        head_ = new Node<T>(value, head_);
        ++size_;
    }

    void push_head(const LinkedList& other) {
        if (other.head_ == nullptr) {
            return;
        }

        Node<T>* new_head = new Node<T>(other.head_->data);
        Node<T>* new_tail = new_head;

        const Node<T>* current = other.head_->next;
        while (current) {
            new_tail->next = new Node<T>(current->data);
            new_tail = new_tail->next;
            current = current->next;
        }

        new_tail->next = head_;
        head_ = new_head;
        size_ += other.size_;
    }

    void push_tail(const T& value) {
        Node<T>* new_node = new Node<T>(value);
        if (head_ == nullptr) {
            head_ = new_node;
        }
        else {
            Node<T>* current = head_;
            while (current->next) { 
                current = current->next;
            }
            current->next = new_node;
        }
        ++size_;
    }

    void push_tail(const LinkedList& other) {
        if (other.head_ == nullptr) {
            return;
        }

        Node<T>* new_head = new Node<T>(other.head_->data);
        Node<T>* new_tail = new_head;

        const Node<T>* current = other.head_->next;
        while (current) {
            new_tail->next = new Node<T>(current->data);
            new_tail = new_tail->next;
            current = current->next;
        }

        if (head_ == nullptr) {
            head_ = new_head;
        }
        else {
            Node<T>* tail = head_;
            while (tail->next) {
                tail = tail->next;
            }
            tail->next = new_head;
        }

        size_ += other.size_;
    }

    void pop_head() {
        if (head_ == nullptr) {
            throw std::out_of_range("Cannot pop from an empty list");
        }
        Node<T>* temp = head_;
        head_ = head_->next;
        delete temp;
        --size_;
    }

    void pop_tail() {
        if (head_ == nullptr) {
            throw std::out_of_range("Cannot pop from an empty list");
        }
        if (head_->next == nullptr) {
            delete head_;
            head_ = nullptr;
        }
        else {
            Node<T>* current = head_;
            while (current->next->next) {
                current = current->next;
            }
            delete current->next;
            current->next = nullptr;
        }
        --size_;
    }

    void delete_node(const T& value) {
        while (head_ && head_->data == value) {
            pop_head();
        }
        if (head_ == nullptr) {
            return;
        }
        Node<T>* current = head_;
        while (current->next) {
            if (current->next->data == value) {
                Node<T>* to_delete = current->next;
                current->next = to_delete->next;
                delete to_delete;
                --size_;
            }
            else {
                current = current->next;
            }
        }
    }

    T& operator[](std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        Node<T>* current = head_;
        for (std::size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    const T& operator[](std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        const Node<T>* current = head_;
        for (std::size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    friend std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list) {
        const Node<T>* current = list.head_;
        while (current) {
            os << current->data << " ";
            current = current->next;
        }
        return os;
    }
};

template <typename T>
void print_reverse(const LinkedList<T>& list) {
    for (std::size_t i = list.get_size(); i > 0; --i) {
        std::cout << list[i - 1] << " ";
    }
    std::cout << "\n";
}

int main() {
    try {
        LinkedList<int> list(5, 10, 99);
        std::cout << "Original list: ";
        std::cout << list << "\n";

        std::cout << "Reversed list: ";
        print_reverse(list);
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 1;
    }
    return 0;
}