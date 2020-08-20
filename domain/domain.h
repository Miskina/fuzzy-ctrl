#ifndef DOMAIN_H
#define DOMAIN_H

#include <ostream>
#include <tuple>

#include "simple_domain.h"
#include "composite_domain.h"


namespace domain
{
	
	template<typename Domain>
	struct domain_size
	{
		enum { value = 1};
	};
	
	template<unsigned int N>
	struct domain_size<composite_domain<N>>
	{
		enum { value = N};	
	};
	
	template<unsigned int N>
	struct domain_for_size
	{
		using type = composite_domain<N>;	
	};
	
	template<>
	struct domain_for_size<1>
	{
		using type = simple_domain;	
	};
	
	constexpr simple_domain int_range(int start, int end)
	{
		return simple_domain(start, end);
	}

    
    template<typename ... Domains>
	struct domain_combine_helper{ };
	
	template<typename ... Domains>
	struct domain_combine_helper<simple_domain, Domains...> : domain_combine_helper<Domains...>
	{
		constexpr domain_combine_helper(const simple_domain& s_domain, const Domains& ... domains) : domain_combine_helper<Domains...>(domains...),
																									 sd(s_domain)
		{}
		
		static constexpr unsigned int size = 1 + domain_combine_helper<Domains...>::size;
		
		constexpr auto get_as_tuple() const noexcept
		{
			return std::tuple_cat(std::tuple<const simple_domain *>{&sd},
								  domain_combine_helper<Domains...>::get_as_tuple());
		}
		
		private:
			const simple_domain& sd;
	};
	
	template<unsigned int N, typename ... Domains>
	struct domain_combine_helper<composite_domain<N>, Domains...> : domain_combine_helper<Domains...>
	{
		constexpr domain_combine_helper(const composite_domain<N>& c_domain, const Domains& ... domains) : domain_combine_helper<Domains...>(domains...),
																										   cd(c_domain)
		{}
		
		static constexpr unsigned int size = N + domain_combine_helper<Domains...>::size;
		
		constexpr auto get_as_tuple() const noexcept
		{
			return std::tuple_cat(get_as_tuple_impl(std::make_index_sequence<N>()),
													domain_combine_helper<Domains...>::get_as_tuple());
		}
		
		private:
			const composite_domain<N>& cd;
			
			template<size_t ... I>
			constexpr auto get_as_tuple_impl(std::index_sequence<I...>) const noexcept
			{
				return std::tuple(&cd.component(I)...);
			}
	};
	
	template<>
	struct domain_combine_helper<>
	{
		static constexpr unsigned int size = 0;
		
		constexpr std::tuple<> get_as_tuple() const noexcept
		{
			return std::tuple<>();
		}
	};
	
	template<typename T, typename ... Ts>
	using array_help = std::array<T, 1 + sizeof...(Ts)>;
	
	template<typename T, typename ... Ts, size_t ... I>
	static constexpr inline array_help<T, Ts...> tuple_2_array(std::tuple<T, Ts...>&& t,
													 		   std::index_sequence<I...>)
	{
		return array_help<T, Ts...>{std::get<I>(t)...};
	}
	
	template<typename ... Domains>
	composite_domain<domain_combine_helper<Domains...>::size> combine(const Domains& ... domains)
    {
    	using Helper = domain_combine_helper<Domains...>;
		Helper helper(domains...);
		
		return composite_domain<Helper::size>(tuple_2_array(helper.get_as_tuple(), std::make_index_sequence<Helper::size>()));
		
//	    return composite_domain<sizeof...(Domains)>({&domains...});
    }
};




#endif
