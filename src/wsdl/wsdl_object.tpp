template<class D>
D* wsdl::WSDL_Object<D>::get() const {
    return ptr.get();
}

template<class D>
template<typename... Args>
void wsdl::WSDL_Object<D>::reset(Args&&... args) {
    ptr.reset(std::forward<Args>(args)...);
}

