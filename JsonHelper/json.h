#ifndef __JsonHelper__H__  
#define __JsonHelper__H__ 

#include <rapidjson/document.h>
#include <rapidjson/error/en.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>


namespace json_helper 
{
	class JsonHelper
	{
 		public:	
		//private:
  		explicit JsonHelper(rapidjson::Type type);

 		public:
  		enum class ParseMode { Iterative, Recursive };

  		JsonHelper();
  		JsonHelper(JsonHelper&&) = default;
  		JsonHelper& operator=(JsonHelper&&) = default;

  		// Create a JsonHelper wrapper for an Object (map).
		static JsonHelper NewObject();

  		// Create a JsonHelper wrapper for an Array (list).
  		static JsonHelper NewArray();

  		// Create a JsonHelper wrapper from an existing value.
  		static JsonHelper NewFromValue(const rapidjson::Value& value);

 		public:
  		// Make a JsonHelper object (map).
 	    rapidjson::Document GetObject() const;

  		// Make a JsonHelper array (list).
  		rapidjson::Document GetArray() const;

  		// Add a JsonHelper object or array to a list.
  		void Push(rapidjson::Value& value);

  		// Add a JsonHelper object or array to a list.
  		void Push(rapidjson::Value& value, rapidjson::Value& arr);

  		// Add a size_t to a JsonHelper array.
  		void Push(size_t value);

  	    // Add a size_t to a JsonHelper array.
  	    void Push(size_t value, rapidjson::Value& arr);

  		// Add a copy of a string to a JsonHelper array.
  		void PushCopy(const std::string& value);

  		// Add a reference to a string to a JsonHelper array.
  		void PushCopy(const std::string& value, rapidjson::Value& arr);

   /**
   * @brief Add a string value to a JsonHelper object by copying the contents.
   *
   * This will Add the key and value to an input document. If the key exists
   * the value will be replaced.
   * The input document must be an object type.
   */
 		void AddCopy(const std::string& key, const std::string& value, rapidjson::Value& obj);

  /**
   * @brief Add a string value to a JsonHelper object by copying the contents.
   *
   * This will Add the key and value to the JsonHelper document. If the key exists
   * the value will be replaced.
   * The document must be an object type.
   */
  		void AddCopy(const std::string& key, const std::string& value);

  /**
   * @brief Add a string value to a JsonHelper object by referencing the contents.
   *
   * The string value must live longer than the document's use.
   *
   * This will Add the key and value to an input document. If the key exists
   * the value will be replaced.
   * The input document must be an object type.
   */
 		 void AddRef(const std::string& key, const std::string& value, rapidjson::Value& obj);

  /**
   * @brief Add a string value to a JsonHelper object by referencing the contents.
   *
   * The string value must live longer than the document's use.
   *
   * This will Add the key and value to the JsonHelper document. If the key exists
   * the value will be replaced.
   * The input document must be an object type.
   */
  		void AddRef(const std::string& key, const std::string& value);

  /**
   * @brief Add a string value to a JsonHelper object by copying the contents.
   *
   * This is basically and alias for AddCopy()
   *
   * This will Add the key and value to an input document. If the key exists
   * the value will be replaced.
   * The input document must be an object type.
   */
  		void Add(const std::string& key, const std::string& value, rapidjson::Value& obj);

  /**
   * @brief Add a string value to a JsonHelper object by copying the contents.
   *
   * This is basically and alias for AddCopy().
   *
   * This will Add the key and value to the JsonHelper document. If the key exists
   * the value will be replaced.
   * The document must be an object type.
   */
  		void Add(const std::string& key, const std::string& value);

  /**
   * @brief Add a char* value to a JsonHelper object by copying the contents.
   *
   * This will Add the key and value to an input document. If the key exists
   * the value will be replaced.
   * The input document must be an object type.
   */
  		void Add(const std::string& key, const char* value, rapidjson::Value& obj);

  /**
   * @brief Add a char* value to a JsonHelper object by copying the contents.
   *
   * This will Add the key and value to the JsonHelper document. If the key exists
   * the value will be replaced.
   * The document must be an object type.
   */
  		void Add(const std::string& key, const char* value);

  /**
   * @brief Add a int value to a JsonHelper object by copying the contents.
   *
   * This will Add the key and value to an input document. If the key exists
   * the value will be replaced.
   * The input document must be an object type.
   */
  		void Add(const std::string& key, int value, rapidjson::Value& obj);

  /**
   * @brief Add a int value to a JsonHelper object by copying the contents.
   *
   * This will Add the key and value to the JsonHelper document. If the key exists
   * the value will be replaced.
   * The document must be an object type.
   */
  		void Add(const std::string& key, int value);

  /**
   * @brief Add a long value to a JsonHelper object by copying the contents.
   *
   * This will Add the key and value to an input document. If the key exists
   * the value will be replaced.
   * The input document must be an object type.
   */
  		void Add(const std::string& key, long value, rapidjson::Value& obj);

  /**
   * @brief Add a long value to a JsonHelper object by copying the contents.
   *
   * This will Add the key and value to the JsonHelper document. If the key exists
   * the value will be replaced.
   * The document must be an object type.
   */
  		void Add(const std::string& key, long value);

  /**
   * @brief Add a long long to a JsonHelper object by copying the
   * contents.
   *
   * This will Add the key and value to an input document. If the key exists
   * the value will be replaced.
   * The input document must be an object type.
   */
  		void Add(const std::string& key, long long value, rapidjson::Value& obj);
  /**
   * @brief Add a long long to a JsonHelper object by copying the
   * contents.
   *
   * This will Add the key and value to the JsonHelper document. If the key exists
   * the value will be replaced.
   * The document must be an object type.
   */
  		void Add(const std::string& key, long long value);

  /**
   * @brief Add an unsigned int value to a JsonHelper object by copying the contents.
   *
   * This will Add the key and value to an input document. If the key exists
   * the value will be replaced.
   * The input document must be an object type.
   */
  		void Add(const std::string& key, unsigned int value, rapidjson::Value& obj);

  /**
   * @brief Add an unsigned int value to a JsonHelper object by copying the contents.
   *
   * This will Add the key and value to the JsonHelper document. If the key exists
   * the value will be replaced.
   * The document must be an object type.
   */
  		void Add(const std::string& key, unsigned int value);

  /**
   * @brief Add an unsigned long value to a JsonHelper object by copying the contents.
   *
   * This will Add the key and value to an input document. If the key exists
   * the value will be replaced.
   * The input document must be an object type.
   */
  		void Add(const std::string& key, unsigned long value, rapidjson::Value& obj);

  /**
   * @brief Add an unsigned long value to a JsonHelper object by copying the contents.
   *
   * This will Add the key and value to the JsonHelper document. If the key exists
   * the value will be replaced.
   * The document must be an object type.
   */
  		void Add(const std::string& key, unsigned long value);

  /**
   * @brief Add an unsigned long long to a JsonHelper object by copying the
   * contents.
   *
   * This will Add the key and value to an input document. If the key exists
   * the value will be replaced.
   * The input document must be an object type.
   */
  		void Add(const std::string& key, unsigned long long value, rapidjson::Value& obj);
  /**
   * @brief Add an unsigned long long to a JsonHelper object by copying the
   * contents.
   *
   * This will Add the key and value to the JsonHelper document. If the key exists
   * the value will be replaced.
   * The document must be an object type.
   */
  		void Add(const std::string& key, unsigned long long value);

  /**
   * @brief Add a double value to a JsonHelper object by copying the contents.
   *
   * This will Add the key and value to an input document. If the key exists
   * the value will be replaced.
   * The input document must be an object type.
   */
  		void Add(const std::string& key, double value, rapidjson::Value& obj);
  /**
   * @brief Add an double value to a JsonHelper object by copying the contents.
   *
   * This will Add the key and value to the JsonHelper document. If the key exists
   * the value will be replaced.
   * The document must be an object type.
   */
  		void Add(const std::string& key, double value);

  /**
   * @brief Add a bool value to a JsonHelper object by copying the contents.
   *
   * This will Add the key and value to an input document. If the key exists
   * the value will be replaced.
   * The input document must be an object type.
   */
  		void Add(const std::string& key, bool value, rapidjson::Value& obj);

  /**
   * @brief Add a bool value to a JsonHelper object by copying the contents.
   *
   * This will Add the key and value to the JsonHelper document. If the key exists
   * the value will be replaced.
   * The document must be an object type.
   */
  		void Add(const std::string& key, bool value);

  		// Add a JsonHelper document as a member.
  		void Add(const std::string& key, const rapidjson::Value& value);

  		// Add a JsonHelper document as a member of another document.
 		void Add(const std::string& key, const rapidjson::Value& value, rapidjson::Value& obj);

  /**
   * @brief Copy a JsonHelper object/array into the document.
   *
   * The type of the base document may change, be careful.
   */
  		void CopyFrom(const rapidjson::Value& value, rapidjson::Value& target);

  /**
   * @brief Copy a JsonHelper object/array into the document.
   *
   * The type of the base document may change, be careful.
   */
  		void CopyFrom(const rapidjson::Value& value);

  		// Convert this document to a JsonHelper string.
  		bool ToString(std::string& str) const;

  		// Convert this document to a formatted JsonHelper string.
  		bool ToPrettyString(std::string& str, size_t indentCharCount = 2) const;

  		// Helper to convert a string into JsonHelper.
 		bool FromString(const std::string& str, ParseMode parse_mode = ParseMode::Recursive);

  		// Merge members of source into target, must both be objects.
  		void MergeObject(rapidjson::Value& target_obj, rapidjson::Value& source_obj);

  		void MergeArray(rapidjson::Value& target_arr, rapidjson::Value& source_arr);

  		//  internal document containing the allocator.
  		rapidjson::Document& GetDoc();

  		// Access the internal document containing the allocator.
  		const rapidjson::Document& GetDoc() const;

 		public:
  		// Get the value as a 'size' or 0.
  		static std::uint64_t ValueToSize(const rapidjson::Value& value);

  		// Get the value as a 'bool' or false.
  		static bool ValueToBool(const rapidjson::Value& value);

		public:
		bool     FindKey(const JsonHelper& json, std::string& key, std::string& value);
		int64_t  FindKey(const JsonHelper& json, std::string& key);

 		private:
  		rapidjson::Document doc_;
  		decltype(rapidjson::kObjectType) type_;
};


} // namespace json_helper

#endif /* __JsonHelper__H__ */
