#include <stdexcept>
#include "customer/customer_archive.hpp"
#include "customer/in_memory_store.hpp"

namespace customer 
{
    bool isValidColor(Color color) 
    {
        switch (color) 
        {
            case Color::Blue:
            case Color::Green:
            case Color::Violet:
            case Color::Red:
            case Color::Yellow:
            case Color::Turquoise:
            case Color::White:
                return true;
            default:
                return false;
        }
    }
    CustomerArchive::CustomerArchive()
        : store_(std::make_shared<InMemoryCustomerStore>()) 
    {
    }
    CustomerArchive::CustomerArchive(std::shared_ptr<ICustomerStore> store)
        : store_(std::move(store)) 
    {
        if (!store_) 
        {
            throw std::invalid_argument("store must not be null");
        }
    }
    bool CustomerArchive::addCustomer(const Customer& customer) 
    {
        if (!customer.isComplete()) 
        {
            return false;
        }
        if (!fitsLegacy(customer)) 
        {
            return false;
        }
        if (!isValidColor(customer.favorite_color)) 
        {
            return false;
        }
        return store_->add(customer);
    }
    std::optional<Customer> CustomerArchive::getById(int id) const 
    {
        return store_->getById(id);
    }
    std::vector<Customer> CustomerArchive::getAll() const 
    {
        return store_->getAll();
    }
}
