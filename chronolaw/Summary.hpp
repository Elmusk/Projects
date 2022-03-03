
#ifndef _SUMMARY_HPP
#define _SUMMARY_HPP

#include "cpplang.hpp"

#if __cpluscplus > 201703L
#include <ranges>
#endif

#include "SalesData.hpp"
#include "SpinLock.hpp"

BEGIN_NAMESPACE(cpp_note)

class Summary final
{
public:
    using this_type = Summary;
public:
    using sales_type = SalesData;
    using lock_type = SpinLock;
    using lock_guard_type = SpinLockGuard;

    using string_type = std::string;
    using map_type = std::map<string_type, sales_type>;
    using minmax_sales_type = std::pair<string_type, string_type>;

public:
    Summary() = default;
    ~Summary() = default;

    Summary(const this_type&) = delete;
    Summary& operator=(const this_type&) = delete;
private:
    mutable lock_type m_lock;
    map_type m_sales;
public:
    void add_sales(const sales_type& s)
    {
        lock_guard_type guard(m_lock);

        const auto& id = s.id();

        // not found
        if (m_sales.find(id) == m_sales.end()) {
            m_sales[id] = s;    // 没找到就添加元素
            return;
        }

        // found
        // you should use iter to optimize it
        m_sales[id].inc_sold(s.sold());    //找到了就修改销量
        m_sales[id].inc_revenue(s.revenue());    //修改利润
    }

    minmax_sales_type minmax_sales() const
    {
        lock_guard_type guard(m_lock);

        if (m_sales.empty()) {
            return {};
        }

#if __cplusplus <= 201703L
        auto ret = std::minmax_element(
            std::begin(m_sales), std::end(m_sales),
            [](const auto& a, const auto& b)
            {
                return a.second.sold() < b.second.sold();
            });

        auto min_pos = std::get<0>(ret);
        auto max_pos = std::get<1>(ret);

#else
        auto [min_pos, max_pos] =
            std::ranges::minmax_element(
                m_sales, {},
                [](const auto& x) {
                    return x.second.sold();
                });
#endif

        return {min_pos->second.id(), max_pos->second.id()};
    }
};

END_NAMESPACE(cpp_note)

#endif


