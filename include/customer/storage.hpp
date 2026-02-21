#pragma once
#include <optional>
#include <vector>
#include "customer.h"

namespace customer 
{
    // Storage abstraction for customer records.
    class ICustomerStore 
    {
    public:
        virtual ~ICustomerStore() = default;
        virtual bool add(const Customer& customer) = 0;
        virtual std::optional<Customer> getById(int id) const = 0;
        virtual std::vector<Customer> getAll() const = 0;
    };
}
