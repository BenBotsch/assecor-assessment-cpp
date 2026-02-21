#pragma once
#include <map>
#include <mutex>
#include "customer/storage.hpp"

namespace customer 
{
    // In-memory storage backend.
    class InMemoryCustomerStore final : public ICustomerStore 
    {
    public:
        bool add(const Customer& customer) override;
        std::optional<Customer> getById(int id) const override;
        std::vector<Customer> getAll() const override;
    private:
        mutable std::mutex mutex_;
        std::map<int, Customer> customers_by_id_;
    };
}
