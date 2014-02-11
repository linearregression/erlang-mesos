#ifndef __MESOS_C_UTILS_HPP__
#define __MESOS_C_UTILS_HPP__

//#include <string>
//#include <vector>

#include "mesos/mesos.pb.h"
#include "erl_nif.h"

template <class T> 
ERL_NIF_TERM pb_obj_to_binary(ErlNifEnv *env, const T& obj)  {
    ErlNifBinary res;
    enif_alloc_binary(obj.ByteSize(), &res); // TODO : do I need to dealloc this?
    obj.SerializeToArray(res.data, res.size);
    return enif_make_binary(env, &res);
}

template<typename T> inline bool deserialize(T& ret, void* data, size_t size)
  {
    if (!ret.ParseFromArray(data, size)) {
      printf("Deserialization failed\n");
      return false;
    }
    return true;
}

template<typename T> inline bool deserialize(T& ret, ErlNifBinary* obj) {
  if (obj == NULL) {
    return false;
  }
  return deserialize<T>(ret, obj->data, obj->size);
}
  /*
  template<typename T> inline ProtobufObj serialize(T& obj, std::string& encoded)
  {
    ProtobufObj pbObj;

    std::string str;
    obj.SerializeToString(&str);
    encoded = str;
    pbObj.data = (void*)encoded.c_str();
    pbObj.size = encoded.length();

    return pbObj;
  }*/
/*
  ProtobufObj inline serialize(const std::string& str)
  {
    ProtobufObj pbObj;
    pbObj.data = (void*)str.c_str();
    pbObj.size = str.length();

    return pbObj;
  }
*/
/*
  template<typename T> inline bool deserialize(
      std::vector<T>& ret,
      void* data,
      size_t size)
  {
    char *end = (char*)data + size;
    for (char* cur = (char*)data; cur < end;) {
      uint64_t length = *(uint64_t*)cur;
      T obj;
      if (!obj.ParseFromArray(cur + sizeof(uint64_t), length)) {
        printf("Deserialization failed\n");
        return false;
      }
      ret.push_back(obj);

      cur += (sizeof(uint64_t) + length);
    }
    return true;
  }*/
/*
  template<typename T> inline bool deserialize(std::vector<T>& ret, ProtobufObj* obj)
  {
    if (obj == NULL) {
      return false;
    }
    return deserialize<T>(ret, obj->data, obj->size);
  }
*/
  /*
  template<typename T> inline bool deserialize(T& ret, void* data, size_t size)
  {
    if (!ret.ParseFromArray(data, size)) {
      printf("Deserialization failed\n");
      return false;
    }
    return true;
  }*/
/*
  template<typename T> inline bool deserialize(T& ret, ProtobufObj* obj) {
    if (obj == NULL) {
      return false;
    }
    return deserialize<T>(ret, obj->data, obj->size);
  }*/
#endif
