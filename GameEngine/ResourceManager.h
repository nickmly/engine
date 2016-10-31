#include <map>
#include <vector>
#include <sstream>

using namespace std;
template <class ResourceType>
class ResourceManager {
private:
	typedef ResourceType* Handle;
	map<string, Handle> *table;
public:
	ResourceManager() {
		table = new map<string, Handle>();
	}

	//Insert a resource into the map using a key
	void Put(string &key, ResourceType* res) {
		table->insert(make_pair(key, res));
	}

	//Gets a resource by looking for it's key
	Handle Get(string &key) {
		return table->at(key);
	}

	//Gets a resource by looking for its handle
	ResourceType Get(Handle handle) {
		map<string, Handle>::iterator it = table->begin();
		while (it != table->end()) {
			if (it->second == handle)
			{
				return *it->second;
			}
			it++;
		}
		return NULL;
	}

	//Removes a resource using its key
	void Remove(string &key) {
		table->erase(key);
	}

	//Remove all resources
	void RemoveAll() {
		table->clear();
	}

	//Return the size of the map
	int Size() {
		return table->size();
	}

	//Get a string value of the all the resources in the map
	string ToString() {
		map<string, Handle>::iterator it = table->begin();
		string total;
		while (it != table->end()) {
			//Convert the int to a string
			stringstream convert;
			int i = *it->second;
			convert << i;
			string result = convert.str();
			//
			
			total += result + string(", ");
			it++;
		}
		return total;
	}
};