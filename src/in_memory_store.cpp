#include "customer/in_memory_store.hpp"
#include <utility>

namespace customer 
{
    bool InMemoryCustomerStore::add(const Customer& customer) 
    {
        std::lock_guard<std::mutex> lock(mutex_);
        const auto [it, inserted] = customers_by_id_.emplace(customer.id, customer);
        return inserted;
    }
    std::optional<Customer> InMemoryCustomerStore::getById(int id) const 
    {
        std::lock_guard<std::mutex> lock(mutex_);
        const auto it = customers_by_id_.find(id);
        if (it == customers_by_id_.end()) 
        {
            return std::nullopt;
        }
        return it->second;
    }
    std::vector<Customer> InMemoryCustomerStore::getAll() const 
    {
        std::lock_guard<std::mutex> lock(mutex_);
        std::vector<Customer> out;
        out.reserve(customers_by_id_.size());
        for (const auto& [_, customer] : customers_by_id_) 
        {
            out.push_back(customer);
        }
        return out;
    }
}
