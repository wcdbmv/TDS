#include <cassert>

template <typename T>
QueueLinkedList<T>::QueueLinkedList()
	: IQueue<T>(), prehead_(new Node<T>()) {
		tail_ = prehead_;
}

template <typename T>
QueueLinkedList<T>::~QueueLinkedList() {
	clear();
	delete prehead_;
}

template <typename T>
void QueueLinkedList<T>::push(const T data) {
	tail_ = tail_->next = new Node<T>(data);
	++IQueue<T>::size_;
}

template <typename T>
T QueueLinkedList<T>::pop() {
	assert(!IQueue<T>::is_empty());

	Node<T>* tmp = prehead_;
	prehead_ = prehead_->next;
	delete tmp;
	--IQueue<T>::size_;
	return prehead_->data;
}

template <typename T>
T QueueLinkedList<T>::top() const {
	assert(!IQueue<T>::is_empty());

	return prehead_->next->data;
}

template <typename T>
bool QueueLinkedList<T>::is_full() const {
	return false;
}

template <typename T>
void QueueLinkedList<T>::clear() {
	Node<T>* tmp;
	Node<T>* head_ = prehead_->next;
	while (head_) {
		tmp = head_;
		head_ = head_->next;
		delete tmp;
	}
	tail_ = prehead_;
	IQueue<T>::size_ = 0;
}

template <typename T>
size_t QueueLinkedList<T>::vtop() const {
	assert(!IQueue<T>::is_empty());

	return prehead_->next;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, QueueLinkedList<T>& qll) {
	Node<T>* curr = qll.prehead_;
	while ((curr = curr->next))
		os << curr->data << ' ';
	return os;
}

template <typename T>
double QueueLinkedList<T>::avgtime() const {
	double sum = 0.0;
	if (!IQueue<T>::size_)
		return sum;
	Node<T>* run = prehead_;
	while ((run = run->next))
		sum += run->data.time;
	return sum / IQueue<T>::size_;
}

template <typename T>
void QueueLinkedList<T>::updqueue(double up) {
	Node<T>* run = prehead_;
	while ((run = run->next))
		run->data.time += up;
}
