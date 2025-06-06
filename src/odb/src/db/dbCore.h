// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2019-2025, The OpenROAD Authors

#pragma once

///
/// This file contains the core objects that everything is
/// built from.
///
/// The core objects are:
///
///  dbId - included
///  dbObjectTable
///  dbObjectPage
///  dbTablePage
///

#include <boost/container/flat_map.hpp>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "dbAttrTable.h"
#include "odb/dbId.h"
#include "odb/dbObject.h"
#include "odb/odb.h"
namespace utl {
class Logger;
}
namespace odb {

class _dbDatabase;
class _dbProperty;
class dbObjectTable;
template <typename T>
class dbHashTable;
template <typename T>
class dbIntHashTable;
template <typename T>
class dbMatrix;
template <class T, const uint P, const uint S>
class dbPagedVector;

#define DB_ALLOC_BIT 0x80000000
#define DB_OFFSET_MASK (~DB_ALLOC_BIT)

using GetObjTbl_t = dbObjectTable* (dbObject::*) (dbObjectType);

struct MemInfo
{
  std::map<const char*, MemInfo> children_;
  int cnt{0};
  uint64_t size{0};

  void add(const char* str)
  {
    if (str) {
      cnt++;
      size += strlen(str);
    }
  }

  void add(const std::string& str) { add(str.c_str()); }

  template <typename T>
  void add(const std::vector<T>& vec)
  {
    cnt += 1;
    size += vec.size() * sizeof(T);
  }

  template <class T, const uint P, const uint S>
  void add(const dbPagedVector<T, P, S>& vec)
  {
    cnt += 1;
    size += vec.size() * sizeof(T);
  }

  template <typename T>
  void add(const dbHashTable<T>& table)
  {
    cnt += 1;
    size += table._hash_tbl.size() * sizeof(dbId<T>);
  }

  template <typename T>
  void add(const dbIntHashTable<T>& table)
  {
    cnt += 1;
    size += table._hash_tbl.size() * sizeof(dbId<T>);
  }

  template <typename T>
  void add(const dbMatrix<T>& matrix)
  {
    cnt += 1;
    size += matrix.numElems() * sizeof(T);
  }

  template <typename Key, typename T>
  void add(const std::map<Key, T>& map)
  {
    cnt += 1;
    size += map.size() * (sizeof(Key) + sizeof(T));
  }

  template <typename T>
  void add(const std::map<std::string, T>& map)
  {
    cnt += 1;
    size += map.size() * (sizeof(std::string) + sizeof(T));
    MemInfo& key_info = children_["key"];
    for (const auto& [key, value] : map) {
      key_info.cnt += 1;
      key_info.size += key.size();
    }
  }

  template <typename Key, typename T>
  void add(const std::unordered_map<Key, T>& map)
  {
    cnt += 1;
    size += map.size() * (sizeof(Key) + sizeof(T));
  }

  template <typename Key, typename T>
  void add(const boost::container::flat_map<Key, T>& map)
  {
    cnt += 1;
    size += map.size() * (sizeof(Key) + sizeof(T));
  }

  template <typename T>
  void add(const std::unordered_map<std::string, T>& map)
  {
    cnt += 1;
    size += map.size() * (sizeof(std::string) + sizeof(T));
    MemInfo& key_info = children_["key"];
    for (const auto& [key, value] : map) {
      key_info.cnt += 1;
      key_info.size += key.size();
    }
  }

  template <typename T>
  void add(const std::set<T>& set)
  {
    cnt += 1;
    size += set.size() * sizeof(T);
  }
};

///////////////////////////////////////////////////////////////
/// _dbObject definition
///////////////////////////////////////////////////////////////
class _dbObject : public dbObject
{
 private:
  uint _oid;

 public:
  _dbDatabase* getDatabase() const;
  dbObjectTable* getTable() const;
  dbObjectPage* getObjectPage() const;
  dbObject* getOwner() const;
  dbObjectType getType() const;
  uint getOID() const;
  utl::Logger* getLogger() const;

  template <class T>
  friend class dbTable;
  template <class T>
  friend class dbArrayTable;
};

///////////////////////////////////////////////////////////////
/// dbObjectTable definition
///////////////////////////////////////////////////////////////
class dbObjectTable
{
 public:
  // NON-PERSISTANT DATA
  _dbDatabase* _db;
  dbObject* _owner;
  dbObjectType _type;
  uint _obj_size;
  dbObjectTable* (dbObject::*_getObjectTable)(dbObjectType type);

  // PERSISTANT DATA
  dbAttrTable<dbId<_dbProperty>> _prop_list;

  virtual ~dbObjectTable() = default;
  dbObjectTable();
  dbObjectTable(_dbDatabase* db,
                dbObject* owner,
                dbObjectTable* (dbObject::*m)(dbObjectType),
                dbObjectType type,
                uint size);

  dbId<_dbProperty> getPropList(uint oid) { return _prop_list.getAttr(oid); }

  void setPropList(uint oid, const dbId<_dbProperty>& propList)
  {
    _prop_list.setAttr(oid, propList);
  }

  virtual dbObject* getObject(uint id, ...) = 0;
  virtual bool validObject(uint id, ...) = 0;

  dbObjectTable* getObjectTable(dbObjectType type)
  {
    return (_owner->*_getObjectTable)(type);
  }
};

///////////////////////////////////////////////////////////////
/// _dbFreeObject definition - free-list object
///////////////////////////////////////////////////////////////

class _dbFreeObject : public _dbObject
{
 public:
  uint _next;
  uint _prev;
};

///////////////////////////////////////////////////////////////
/// dbObjectPage definition
///////////////////////////////////////////////////////////////
class dbObjectPage
{
 public:
  // NON-PERSISTANT DATA
  dbObjectTable* _table;
  uint _page_addr;
  uint _alloccnt;

  bool valid_page() const { return _alloccnt != 0; }
};

///////////////////////////////////////////////////////////////
/// dbObjectTable implementation
///////////////////////////////////////////////////////////////
inline dbObjectTable::dbObjectTable()
{
  _db = nullptr;
  _owner = nullptr;
}

inline dbObjectTable::dbObjectTable(_dbDatabase* db,
                                    dbObject* owner,
                                    dbObjectTable* (dbObject::*m)(dbObjectType),
                                    dbObjectType type,
                                    uint size)
{
  _db = db;
  _owner = owner;
  _getObjectTable = m;
  _type = type;

  // Objects must be greater than 16-bytes
  assert(size >= sizeof(_dbFreeObject));
  _obj_size = size;
}

///////////////////////////////////////////////////////////////
/// _dbObject inlines
///////////////////////////////////////////////////////////////

inline _dbObject* dbObject::getImpl()
{
  return (_dbObject*) this;
}

inline const _dbObject* dbObject::getImpl() const
{
  return (_dbObject*) this;
}

inline uint _dbObject::getOID() const
{
  dbObjectPage* page = getObjectPage();
  uint offset = (_oid & DB_OFFSET_MASK);
  return page->_page_addr | offset / page->_table->_obj_size;
}

inline dbObjectTable* _dbObject::getTable() const
{
  dbObjectPage* page = getObjectPage();
  return page->_table;
}

inline _dbDatabase* _dbObject::getDatabase() const
{
  dbObjectPage* page = getObjectPage();
  return page->_table->_db;
}

inline dbObject* _dbObject::getOwner() const
{
  dbObjectPage* page = getObjectPage();
  return page->_table->_owner;
}

inline dbObjectType _dbObject::getType() const
{
  dbObjectPage* page = getObjectPage();
  return page->_table->_type;
}

inline dbObjectPage* _dbObject::getObjectPage() const
{
  uint offset = (_oid & DB_OFFSET_MASK);
  char* base = (char*) this - offset;
  dbObjectPage* page = (dbObjectPage*) (base - sizeof(dbObjectPage));
  return page;
}

}  // namespace odb
