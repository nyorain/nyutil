// Copyright (c) 2016 nyorain
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt

///\file Contains a one-dimensional Simplex specialization (Line).

#pragma once

#ifndef NYTL_INCLUDE_LINE_HPP
#define NYTL_INCLUDE_LINE_HPP

#include <nytl/vec.hpp>
#include <nytl/scalar.hpp>
#include <nytl/simplex.hpp>

namespace nytl
{

//typedefs
template<typename P = float> using Line2 = Line<2, P>;
template<typename P = float> using Line3 = Line<3, P>;
template<typename P = float> using Line4 = Line<4, P>;

using Line2f = Line<2, float>;
using Line3f = Line<3, float>;
using Line4f = Line<4, float>;

using Line2i = Line<2, int>;
using Line3i = Line<3, int>;
using Line4i = Line<4, int>;

using Line2ui = Line<2, unsigned int>;
using Line3ui = Line<3, unsigned int>;
using Line4ui = Line<4, unsigned int>;


template<size_t D, typename P>
class Simplex<D, P, 1>
{
public:
	static constexpr std::size_t dim = D;
	static constexpr std::size_t simplexDim = 3;

	using Precision = P;
	using VecType = Vec<D, P>;
	using LineType = Line<D, P>;
	using Size = std::size_t;

	//stl
	using value_type = Precision;
	using size_type = Size;

public:
	VecType a {};
	VecType b {};

public:
	Simplex(const VecType& xa, const VecType& xb) noexcept : a(xa), b(xb) {}
	Simplex() noexcept = default;

	//Simplex
	double size() const { return distance(a, b); }
	VecType center() const { return (a + b) / 2; }

	Vec<2, VecType>& points()
		{ return reinterpret_cast<Vec<2, VecType>&>(*this); }
	const Vec<2, VecType>& points() const
		{ return reinterpret_cast<const Vec<2, VecType>&>(*this); }

	template<size_t OD, typename OP>
	operator Line<OD, OP>() const { return Line<OD, OP>(a, b); }

	//Line-specific
	///Alias for size(). Returns the length of the Line.
	double length() const { return size(); }

	///Returns the Vector that lays between the two points
	VecType difference() const { return b - a; }

	///Returns a normalized (length = 1) gradient Vector.
	VecType gradient() const { return normalize(difference()); }

	///Returns the gradient Vector in relation to the given dimension parameter.
	///If e.g. dim is 0, the x component of the returned gradient Vector will be 1 and all
	///other components will be set in relation.
	VecType gradient(Size dim) const { return difference() / difference()[dim]; }

	///Returns wheter the Line is defined for the given value in the given dimension.
	bool definedAt(const Precision& value, Size dimension = 0) const;

	///Returns the point of the Line at the given value in the given dimension.
	///One should check with definedAt(value, dimension) if the Line is defined for the given
	///value before using this. If it is not, this function will produce a warning and return an
	///empty Vec.
	VecType valueAt(const Precision& value, Size dimension = 0) const;

	///Returns the smallest value the Line is defined for in the given dimension.
	Precision smallestValue(Size dim) const { return min(a[dim], b[dim]); }

	///Returns the greatest value the Line is defined for in the given dimension.
	Precision greatestValue(Size dim) const { return max(a[dim], b[dim]); }
};

//implementation, utility and operators
#include <nytl/bits/line.inl>

}

#endif //header guard
