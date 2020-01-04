template <typename T>
Node<T>::Node(const T data, Node<T>* next)
	: data(data)
	, next(next)
	{ }
