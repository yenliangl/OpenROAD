// *****************************************************************************
// *****************************************************************************
// Copyright 2013, Cadence Design Systems
//
// This  file  is  part  of  the  Cadence  LEF/DEF  Open   Source
// Distribution,  Product Version 5.8.
//
// Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
//    implied. See the License for the specific language governing
//    permissions and limitations under the License.
//
// For updates, support, or to become part of the LEF/DEF Community,
// check www.openeda.org for details.
//
//  $Author: dell $
//  $Revision: #1 $
//  $Date: 2020/09/29 $
//  $State:  $
// *****************************************************************************
// *****************************************************************************

#ifndef defiPropType_h
#define defiPropType_h

#include <cstdio>

#include "defiKRDefs.hpp"

BEGIN_DEF_PARSER_NAMESPACE

// Struct holds the data type for one property, if the property is
// either REAL or INTEGER.
class defiPropType
{
 public:
  defiPropType();
  void Init();

  void Destroy();
  ~defiPropType();

  void setPropType(const char* name, const char type);
  void Clear();

  char propType(char* name) const;
  void bumpProps();

 protected:
  int numProperties_;
  int propertiesAllocated_;
  char** propNames_;  // name.
  char* propTypes_;   // 'R' == "REAL", 'I' == "INTEGER"
};

END_DEF_PARSER_NAMESPACE

#endif
