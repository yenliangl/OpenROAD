// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2021-2025, The OpenROAD Authors

%rename(_print) print;

%define WRAP_OBJECT_OPERATOR(T)
%rename(incr) T::operator++();
%rename(incr_int) T::operator++(int);
%enddef

WRAP_OBJECT_OPERATOR(odb::dbSetIterator<dbBlock>)
WRAP_OBJECT_OPERATOR(odb::dbSetIterator<dbCCSeg>)

%define WRAP_OBJECT_STREAM(T)
%rename(IStream) operator>>(dbIStream &, T &);
%rename(OStream) operator<<(dbOStream &, const T &);
%rename(equal)  odb::T::operator=(const T &);

%enddef
WRAP_OBJECT_STREAM(Point)
WRAP_OBJECT_STREAM(Rect)
WRAP_OBJECT_STREAM(dbTransform)
WRAP_OBJECT_STREAM(_dbViaParams)

