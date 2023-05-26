/**
 * Copyright (c) 2014-present, The osquery authors
 *
 * This source code is licensed as defined by the LICENSE file found in the
 * root directory of this source tree.
 *
 * SPDX-License-Identifier: (Apache-2.0 OR GPL-2.0-only)
 *
 */

#include "json.h"
#include <algorithm>

namespace rj = rapidjson;
using  namespace json_helper;

JsonHelper::JsonHelper(rj::Type type) : type_(type) 
{
	if (type_ == rj::kObjectType) 
	{
		doc_.SetObject();
  	}
	else 
  	{
    	doc_.SetArray();
  	}
}

JsonHelper::JsonHelper() 
{
	type_ = rj::kObjectType;
	doc_.SetObject();
}

JsonHelper JsonHelper::NewObject() 
{
	return JsonHelper(rj::kObjectType);
}

JsonHelper JsonHelper::NewArray() 
{
	return JsonHelper(rj::kArrayType);
}

rj::Document JsonHelper::GetObject() const 
{
	rj::Document line;
	line.SetObject();
	return line;
}

rj::Document JsonHelper::GetArray() const 
{
	rj::Document line;
	line.SetArray();
	return line;
}

void JsonHelper::Push(rj::Value& value) 
{
	assert(type_ == rj::kArrayType);
	Push(value, doc_);
}

void JsonHelper::Push(rj::Value& value, rj::Value& arr) 
{
	arr.PushBack(rj::Value(value, doc_.GetAllocator()).Move(), doc_.GetAllocator());
}

void JsonHelper::Push(size_t value) 
{
	Push(value, doc_);
}

void JsonHelper::Push(size_t value, rj::Value& arr) 
{
  arr.PushBack(rj::Value(static_cast<uint64_t>(value)).Move(), doc_.GetAllocator());
}

void JsonHelper::PushCopy(const std::string& value) 
{
	PushCopy(value, doc_);
}

void JsonHelper::PushCopy(const std::string& value, rj::Value& arr)
{
	rj::Value sc;
  	sc.SetString(value.c_str(), (rapidjson::SizeType)value.size(), doc_.GetAllocator());
  	arr.PushBack(sc.Move(), doc_.GetAllocator());
}

void JsonHelper::Add(const std::string& key, const rj::Value& value) 
{
	Add(key, value, doc_);
}

void JsonHelper::Add(const std::string& key, const rj::Value& value, rj::Value& obj) 
{
	assert(obj.IsObject());
	auto itr = obj.FindMember(key.c_str());
	if (itr != obj.MemberEnd()) 
	{
		obj.RemoveMember(itr);
	}

	obj.AddMember(rj::Value(rj::StringRef(key.c_str()), doc_.GetAllocator()).Move(),
                rj::Value(value, doc_.GetAllocator()).Move(),
                doc_.GetAllocator());
}

void JsonHelper::AddCopy(const std::string& key, const std::string& value, rj::Value& obj) 
{
	assert(obj.IsObject());
	auto itr = obj.FindMember(key.c_str());
	if (itr != obj.MemberEnd()) 
	{
		obj.RemoveMember(itr);
  	}

	rj::Value sc;
  	sc.SetString(value.c_str(), (rapidjson::SizeType)value.size(), doc_.GetAllocator());
 	obj.AddMember(rj::Value(rj::StringRef(key.c_str()), doc_.GetAllocator()).Move(),
                sc.Move(),
                doc_.GetAllocator());
}

void JsonHelper::AddCopy(const std::string& key, const std::string& value) 
{
	AddCopy(key, value, doc_);
}

void JsonHelper::AddRef(const std::string& key, const std::string& value, rj::Value& obj) 
{
	assert(obj.IsObject());
	auto itr = obj.FindMember(key.c_str());
	if (itr != obj.MemberEnd()) 
	{
		obj.RemoveMember(itr);
  	}

  	obj.AddMember(rj::Value(rj::StringRef(key.c_str()), doc_.GetAllocator()).Move(),
                rj::Value(rj::StringRef(value.c_str()), doc_.GetAllocator()).Move(),
                doc_.GetAllocator());
}

void JsonHelper::AddRef(const std::string& key, const std::string& value)
{
	AddRef(key, value, doc_);
}

void JsonHelper::Add(const std::string& key, const std::string& value) 
{
  	AddCopy(key, value);
}

void JsonHelper::Add(const std::string& key, const std::string& value, rj::Value& obj) 
{
	AddCopy(key, value, obj);
}

void JsonHelper::Add(const std::string& key, const char* value, rj::Value& obj) 
{
	assert(obj.IsObject());
	auto itr = obj.FindMember(key.c_str());
	if (itr != obj.MemberEnd()) 
	{
		obj.RemoveMember(itr);
  	}

  	obj.AddMember(rj::Value(rj::StringRef(key.c_str()), doc_.GetAllocator()).Move(),
                rj::Value(value, (rapidjson::SizeType)strlen(value)).Move(),
                doc_.GetAllocator());
}
void JsonHelper::Add(const std::string& key, const char* value) 
{
  	Add(key, value, doc_);
}

void JsonHelper::Add(const std::string& key, int value, rj::Value& obj) 
{
	assert(obj.IsObject());
	auto itr = obj.FindMember(key.c_str());
	if (itr != obj.MemberEnd()) 
	{
		obj.RemoveMember(itr);
  	}

  	obj.AddMember(rj::Value(rj::StringRef(key.c_str()), doc_.GetAllocator()).Move(),
                rj::Value(static_cast<int64_t>(value)).Move(),
                doc_.GetAllocator());
}

void JsonHelper::Add(const std::string& key, int value) 
{
	Add(key, value, doc_);
}

void JsonHelper::Add(const std::string& key, long value, rj::Value& obj) 
{
	assert(obj.IsObject());
	auto itr = obj.FindMember(key.c_str());
	if (itr != obj.MemberEnd()) 
	{
		obj.RemoveMember(itr);
  	}

  	obj.AddMember(rj::Value(rj::StringRef(key.c_str()), doc_.GetAllocator()).Move(),
                rj::Value(static_cast<int64_t>(value)).Move(),
                doc_.GetAllocator());
}

void JsonHelper::Add(const std::string& key, long value) 
{
	Add(key, value, doc_);
}

void JsonHelper::Add(const std::string& key, long long value, rj::Value& obj) 
{
	assert(obj.IsObject());
	auto itr = obj.FindMember(key.c_str());
	if (itr != obj.MemberEnd()) 
	{
		obj.RemoveMember(itr);
  	}
  	obj.AddMember(rj::Value(rj::StringRef(key.c_str()), doc_.GetAllocator()).Move(),
                rj::Value(static_cast<int64_t>(value)).Move(),
                doc_.GetAllocator());
}
void JsonHelper::Add(const std::string& key, long long value) 
{
	Add(key, value, doc_);
}

void JsonHelper::Add(const std::string& key, unsigned int value, rj::Value& obj) 
{
	assert(obj.IsObject());
	auto itr = obj.FindMember(key.c_str());
	if (itr != obj.MemberEnd()) 
	{
		obj.RemoveMember(itr);
  	}

  	obj.AddMember(rj::Value(rj::StringRef(key.c_str()), doc_.GetAllocator()).Move(),
                rj::Value(static_cast<uint64_t>(value)).Move(),
                doc_.GetAllocator());
}

void JsonHelper::Add(const std::string& key, unsigned int value)
{
	Add(key, value, doc_);
}

void JsonHelper::Add(const std::string& key, unsigned long value, rj::Value& obj) 
{
	assert(obj.IsObject());
	auto itr = obj.FindMember(key.c_str());
	if (itr != obj.MemberEnd()) 
	{
		obj.RemoveMember(itr);
  	}

  	obj.AddMember(rj::Value(rj::StringRef(key.c_str()), doc_.GetAllocator()).Move(),
                rj::Value(static_cast<uint64_t>(value)).Move(),
                doc_.GetAllocator());
}

void JsonHelper::Add(const std::string& key, unsigned long value) 
{
	Add(key, value, doc_);
}

void JsonHelper::Add(const std::string& key, unsigned long long value, rj::Value& obj)
{
  	assert(obj.IsObject());
  	auto itr = obj.FindMember(key.c_str());
	if (itr != obj.MemberEnd()) 
	{
    	obj.RemoveMember(itr);
  	}
  	obj.AddMember(rj::Value(rj::StringRef(key.c_str()), doc_.GetAllocator()).Move(),
                rj::Value(static_cast<uint64_t>(value)).Move(),
                doc_.GetAllocator());
}
void JsonHelper::Add(const std::string& key, unsigned long long value) 
{
  	Add(key, value, doc_);
}
void JsonHelper::Add(const std::string& key, double value, rj::Value& obj) 
{
  	assert(obj.IsObject());
  	auto itr = obj.FindMember(key.c_str());
  	if (itr != obj.MemberEnd()) 
	{
    	obj.RemoveMember(itr);
  	}
  	obj.AddMember(rj::Value(rj::StringRef(key.c_str()), doc_.GetAllocator()).Move(),
                rj::Value(value).Move(),
                doc_.GetAllocator());
}
void JsonHelper::Add(const std::string& key, double value) 
{
  	Add(key, value, doc_);
}

void JsonHelper::Add(const std::string& key, bool value, rj::Value& obj) 
{
  	assert(obj.IsObject());
  	auto itr = obj.FindMember(key.c_str());
  	if (itr != obj.MemberEnd()) 
	{
    	obj.RemoveMember(itr);
  	}

  	obj.AddMember(rj::Value(rj::StringRef(key.c_str()), doc_.GetAllocator()).Move(),
                rj::Value(value).Move(),
                doc_.GetAllocator());
}

void JsonHelper::Add(const std::string& key, bool value) 
{
  	Add(key, value, doc_);
}

bool JsonHelper::ToString(std::string& str) const 
{
  	rj::StringBuffer sb;
  	rj::Writer<rj::StringBuffer> writer(sb);
  	doc_.Accept(writer);
  	str = sb.GetString();
  	return true;
}

bool JsonHelper::ToPrettyString(std::string& str, size_t indentCharCount) const 
{
  	rj::StringBuffer sb;
  	rj::PrettyWriter<rj::StringBuffer> writer(sb);
  	writer.SetIndent(' ', (unsigned)indentCharCount);
  	doc_.Accept(writer);
  	str = sb.GetString();
  	return true;
}

bool JsonHelper::FromString(const std::string& str, ParseMode mode) 
{
	rj::ParseResult pr;
  	switch (mode) 
	{
  		case ParseMode::Iterative: 
		{
   	 		pr = doc_.Parse<rj::kParseIterativeFlag>(str.c_str());
   	 		break;
  		}
  		case ParseMode::Recursive: 
		{
    		pr = doc_.Parse(str.c_str());
    		break;
  		}
 	 }

  	if (!pr)
   	{
    	std::string message{"Cannot parse JsonHelper: "};
    	message += GetParseError_En(pr.Code());
    	message += " Offset: ";
    	message += std::to_string(pr.Offset());
    	return false;
  	}
  return true;
}

void JsonHelper::MergeObject(rj::Value& target_obj, rj::Value& source_obj)
{
  	assert(target_obj.IsObject());
  	assert(source_obj.IsObject());
  	for (auto itr = source_obj.MemberBegin(); itr != source_obj.MemberEnd();++itr) 
	{
    	auto titr = target_obj.FindMember(itr->name);
    	if (titr != target_obj.MemberEnd()) 
		{
      		target_obj.RemoveMember(titr);
    	}
    	target_obj.AddMember(itr->name, itr->value, doc_.GetAllocator());
  	}
}

void JsonHelper::MergeArray(rj::Value& target_arr, rj::Value& source_arr) 
{
  	assert(target_arr.IsArray());
  	assert(source_arr.IsArray());
  	for (auto itr = source_arr.Begin(); itr != source_arr.End(); ++itr) 
	{
    	target_arr.PushBack(*itr, doc_.GetAllocator());
  	}
}

JsonHelper JsonHelper::NewFromValue(const rj::Value& value) 
{
  	assert(value.IsObject() || value.IsArray());

  	JsonHelper json_helper;
  	json_helper.type_ = (value.IsArray()) ? rj::kArrayType : rj::kObjectType;
  	json_helper.CopyFrom(value, json_helper.GetDoc());
  	return json_helper;
}

void JsonHelper::CopyFrom(const rapidjson::Value& value, rj::Value& target) 
{
  	target.CopyFrom(value, doc_.GetAllocator());
}

void JsonHelper::CopyFrom(const rj::Value& value) 
{
  	CopyFrom(value, doc_);
}

rj::Document& JsonHelper::GetDoc() 
{
  	return doc_;
}

const rj::Document& JsonHelper::GetDoc() const 
{
  	return doc_;
}

//TODO
std::uint64_t JsonHelper::ValueToSize(const rj::Value& value) 
{
  	if (value.IsString()) 
	{
    	return 0;
	 //return tryTo<std::uint64_t>(std::string{value.GetString()}).takeOr(0_sz);
  	} 
	else if (value.IsNumber()) 
	{
    	return static_cast<size_t>(value.GetUint64());
  	}
  	return 0;
  	//return 0_sz;
}

bool JsonHelper::ValueToBool(const rj::Value& value) 
{
  	if (value.IsBool()) 
	{
    	return value.GetBool();
  	} 
	else if (value.IsString()) 
	{
    	auto b = std::string(value.GetString());
    	std::transform(b.begin(), b.end(), b.begin(), ::tolower);
    	return (b == "true" || b == "t");
  	} 
	else if (value.IsNumber()) 
	{
    	return (value.GetInt() != 0);
  	}
  	return false;
}

bool JsonHelper::FindKey(const JsonHelper& json, std::string& key, std::string& value)
{
	bool ret = false;
    if(json.GetDoc().HasMember(key.c_str()))
    {
		value = "";
        if(json.GetDoc()[key.c_str()].IsString())
        {
            value = json.GetDoc()[key.c_str()].GetString();
        }
        else if(json.GetDoc()[key.c_str()].IsInt())
        {
			value = std::to_string(json.GetDoc()[key.c_str()].GetInt());
        }
        else if(json.GetDoc()[key.c_str()].IsInt64())
        {
			value = std::to_string(json.GetDoc()[key.c_str()].GetInt64());
        }
		ret = value.empty() ? false : true;
    }
    return ret;
}

int64_t FindKey(const JsonHelper& json, std::string& key)
{
    if(json.GetDoc().HasMember(key.c_str()))
    {
        if(json.GetDoc()[key.c_str()].IsString())
        {
            return std::atoi(json.GetDoc()[key.c_str()].GetString());
        }
        else if(json.GetDoc()[key.c_str()].IsInt())
        {
            return json.GetDoc()[key.c_str()].GetInt();
        }
        else if(json.GetDoc()[key.c_str()].IsInt64())
        {
            return json.GetDoc()[key.c_str()].GetInt64();
        }
        return 0;
    }
    return 0;
}

