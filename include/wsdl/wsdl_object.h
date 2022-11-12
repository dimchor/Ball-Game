#pragma once

#include "wsdl.h"

namespace wsdl {
    template<class D>
    class WSDL_Object {
        public:
            WSDL_Object() = default;
            WSDL_Object(const WSDL_Object&) = default;
            WSDL_Object& operator=(const WSDL_Object&) = default;
            WSDL_Object(WSDL_Object&&) = default;
            WSDL_Object& operator=(WSDL_Object&&) = default;

            D* get() const;
        protected:
            template<typename... Args>
            void reset(Args&&...);
        private:
            std::unique_ptr<D, SDL_Delete> ptr { nullptr };
    };
    #include "../../src/wsdl/wsdl_object.tpp"
}

