// *****************************************************************************
// *****************************************************************************
// ATTENTION: THIS IS AN AUTO-GENERATED FILE. DO NOT CHANGE IT!
// *****************************************************************************
// *****************************************************************************
// Copyright 2012, Cadence Design Systems
//
// This  file  is  part  of  the  Cadence  LEF/DEF  Open   Source
// Distribution,  Product Version 5.8.
//
// Licensed under the Apache License, Version 2.0 (the \"License\");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an \"AS IS\" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
//    implied. See the License for the specific language governing
//    permissions and limitations under the License.
//
//
// For updates, support, or to become part of the LEF/DEF Community,
// check www.openeda.org for details.
//
//  $Author: xxx $
//  $Revision: xxx $
//  $Date: xxx $
//  $State: xxx $
// *****************************************************************************
// *****************************************************************************

#define EXTERN extern "C"

#include "defiComponent.h"
#include "defiComponent.hpp"

// Wrappers definitions.
int defiComponentMaskShiftLayer_numMaskShiftLayers(
    const ::defiComponentMaskShiftLayer* obj)
{
  return ((DefParser::defiComponentMaskShiftLayer*) obj)->numMaskShiftLayers();
}

const char* defiComponentMaskShiftLayer_maskShiftLayer(
    const ::defiComponentMaskShiftLayer* obj,
    int index)
{
  return ((const DefParser::defiComponentMaskShiftLayer*) obj)
      ->maskShiftLayer(index);
}

const char* defiComponent_id(const ::defiComponent* obj)
{
  return ((const DefParser::defiComponent*) obj)->id();
}

const char* defiComponent_name(const ::defiComponent* obj)
{
  return ((const DefParser::defiComponent*) obj)->name();
}

int defiComponent_placementStatus(const ::defiComponent* obj)
{
  return ((DefParser::defiComponent*) obj)->placementStatus();
}

int defiComponent_isUnplaced(const ::defiComponent* obj)
{
  return ((DefParser::defiComponent*) obj)->isUnplaced();
}

int defiComponent_isPlaced(const ::defiComponent* obj)
{
  return ((DefParser::defiComponent*) obj)->isPlaced();
}

int defiComponent_isFixed(const ::defiComponent* obj)
{
  return ((DefParser::defiComponent*) obj)->isFixed();
}

int defiComponent_isCover(const ::defiComponent* obj)
{
  return ((DefParser::defiComponent*) obj)->isCover();
}

int defiComponent_placementX(const ::defiComponent* obj)
{
  return ((DefParser::defiComponent*) obj)->placementX();
}

int defiComponent_placementY(const ::defiComponent* obj)
{
  return ((DefParser::defiComponent*) obj)->placementY();
}

int defiComponent_placementOrient(const ::defiComponent* obj)
{
  return ((DefParser::defiComponent*) obj)->placementOrient();
}

const char* defiComponent_placementOrientStr(const ::defiComponent* obj)
{
  return ((const DefParser::defiComponent*) obj)->placementOrientStr();
}

int defiComponent_hasRegionName(const ::defiComponent* obj)
{
  return ((DefParser::defiComponent*) obj)->hasRegionName();
}

int defiComponent_hasRegionBounds(const ::defiComponent* obj)
{
  return ((DefParser::defiComponent*) obj)->hasRegionBounds();
}

int defiComponent_hasEEQ(const ::defiComponent* obj)
{
  return ((DefParser::defiComponent*) obj)->hasEEQ();
}

int defiComponent_hasGenerate(const ::defiComponent* obj)
{
  return ((DefParser::defiComponent*) obj)->hasGenerate();
}

int defiComponent_hasSource(const ::defiComponent* obj)
{
  return ((DefParser::defiComponent*) obj)->hasSource();
}

int defiComponent_hasWeight(const ::defiComponent* obj)
{
  return ((DefParser::defiComponent*) obj)->hasWeight();
}

int defiComponent_weight(const ::defiComponent* obj)
{
  return ((DefParser::defiComponent*) obj)->weight();
}

int defiComponent_maskShiftSize(const ::defiComponent* obj)
{
  return ((DefParser::defiComponent*) obj)->maskShiftSize();
}

int defiComponent_maskShift(const ::defiComponent* obj, int index)
{
  return ((DefParser::defiComponent*) obj)->maskShift(index);
}

int defiComponent_hasNets(const ::defiComponent* obj)
{
  return ((DefParser::defiComponent*) obj)->hasNets();
}

int defiComponent_numNets(const ::defiComponent* obj)
{
  return ((DefParser::defiComponent*) obj)->numNets();
}

const char* defiComponent_net(const ::defiComponent* obj, int index)
{
  return ((const DefParser::defiComponent*) obj)->net(index);
}

const char* defiComponent_regionName(const ::defiComponent* obj)
{
  return ((const DefParser::defiComponent*) obj)->regionName();
}

const char* defiComponent_source(const ::defiComponent* obj)
{
  return ((const DefParser::defiComponent*) obj)->source();
}

const char* defiComponent_EEQ(const ::defiComponent* obj)
{
  return ((const DefParser::defiComponent*) obj)->EEQ();
}

const char* defiComponent_generateName(const ::defiComponent* obj)
{
  return ((const DefParser::defiComponent*) obj)->generateName();
}

const char* defiComponent_macroName(const ::defiComponent* obj)
{
  return ((const DefParser::defiComponent*) obj)->macroName();
}

int defiComponent_hasHalo(const ::defiComponent* obj)
{
  return ((DefParser::defiComponent*) obj)->hasHalo();
}

int defiComponent_hasHaloSoft(const ::defiComponent* obj)
{
  return ((DefParser::defiComponent*) obj)->hasHaloSoft();
}

int defiComponent_hasRouteHalo(const ::defiComponent* obj)
{
  return ((DefParser::defiComponent*) obj)->hasRouteHalo();
}

int defiComponent_haloDist(const ::defiComponent* obj)
{
  return ((DefParser::defiComponent*) obj)->haloDist();
}

const char* defiComponent_minLayer(const ::defiComponent* obj)
{
  return ((const DefParser::defiComponent*) obj)->minLayer();
}

const char* defiComponent_maxLayer(const ::defiComponent* obj)
{
  return ((const DefParser::defiComponent*) obj)->maxLayer();
}

void defiComponent_regionBounds(const ::defiComponent* obj,
                                int* size,
                                int** xl,
                                int** yl,
                                int** xh,
                                int** yh)
{
  ((DefParser::defiComponent*) obj)->regionBounds(size, xl, yl, xh, yh);
}

int defiComponent_hasForeignName(const ::defiComponent* obj)
{
  return ((DefParser::defiComponent*) obj)->hasForeignName();
}

const char* defiComponent_foreignName(const ::defiComponent* obj)
{
  return ((const DefParser::defiComponent*) obj)->foreignName();
}

int defiComponent_foreignX(const ::defiComponent* obj)
{
  return ((DefParser::defiComponent*) obj)->foreignX();
}

int defiComponent_foreignY(const ::defiComponent* obj)
{
  return ((DefParser::defiComponent*) obj)->foreignY();
}

const char* defiComponent_foreignOri(const ::defiComponent* obj)
{
  return ((const DefParser::defiComponent*) obj)->foreignOri();
}

int defiComponent_foreignOrient(const ::defiComponent* obj)
{
  return ((DefParser::defiComponent*) obj)->foreignOrient();
}

int defiComponent_hasFori(const ::defiComponent* obj)
{
  return ((DefParser::defiComponent*) obj)->hasFori();
}

int defiComponent_numProps(const ::defiComponent* obj)
{
  return ((DefParser::defiComponent*) obj)->numProps();
}

char* defiComponent_propName(const ::defiComponent* obj, int index)
{
  return ((DefParser::defiComponent*) obj)->propName(index);
}

char* defiComponent_propValue(const ::defiComponent* obj, int index)
{
  return ((DefParser::defiComponent*) obj)->propValue(index);
}

double defiComponent_propNumber(const ::defiComponent* obj, int index)
{
  return ((DefParser::defiComponent*) obj)->propNumber(index);
}

char defiComponent_propType(const ::defiComponent* obj, int index)
{
  return ((DefParser::defiComponent*) obj)->propType(index);
}

int defiComponent_propIsNumber(const ::defiComponent* obj, int index)
{
  return ((DefParser::defiComponent*) obj)->propIsNumber(index);
}

int defiComponent_propIsString(const ::defiComponent* obj, int index)
{
  return ((DefParser::defiComponent*) obj)->propIsString(index);
}

void defiComponent_print(const ::defiComponent* obj, FILE* fout)
{
  ((DefParser::defiComponent*) obj)->print(fout);
}
