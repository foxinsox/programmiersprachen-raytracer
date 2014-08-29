#ifndef BUW_SDF_READER
#define BUW_SDF_READER

#include "fensterchen.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <glm/glm.hpp>
#include <cmath>



class SDFReader{

public:

	SDFReader(std::string const& path);

	bool load();
	bool load(std::string const& path);
	Scene scene()const;



private:

	std::string filepath;
	bool error;
	std::string error_message;
	Scene scene_;
	std::map<std::string,std::shared_ptr<Material>> materials;

	bool requestCommand(std::stringstream& token_stream);
	bool requestDefinition(std::stringstream& token_stream);
	bool requestMaterial(std::stringstream& token_stream);
	bool requestShape(std::stringstream& token_stream);
	bool requestVec3(std::stringstream& token_stream, glm::vec3& p);
	bool requestFloat(std::stringstream& token_stream, float& f);
	bool requestString(std::stringstream& token_stream, std::string& str);
	bool requestColor(std::stringstream& token_stream, Color& cl);
	void printError(std::stringstream& token_stream, int position, std::string const& error_message);
};

#endif //BUW_SDF_READER