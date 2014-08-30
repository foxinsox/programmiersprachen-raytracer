#include "sdf_reader.hpp"


SDFReader::SDFReader(std::string const& path)
:filepath(path),error(false),scene_(),materials(),shapes(),lights(),cameras(),error_message("Error: could not read SDF"){}




bool SDFReader::load(){

	error = false;
	std::ifstream ifs;
	ifs.open(filepath);

	if(ifs.is_open()){
		while(ifs.good()){
			std::string line;
			std::getline(ifs,line);
			std::stringstream line_stream(line);
			requestCommand(line_stream);  //einstieg
		}
	}
	else{
		std::cout<<"file could not be opened"<<std::endl;
		error = true;
	}
	ifs.close();
	return !error;
};

bool SDFReader::load(std::string const& path){
	filepath = path;
	return load();
};

Scene SDFReader::scene()const{
	return scene_;
};


void 
SDFReader::printError(std::stringstream& line_stream, int pos, std::string const& error_message)
{
	std::cout << error_message << std::endl;
	std::cout << line_stream.str() << std::endl;

	if(pos != -1) {
		pos = line_stream.str().size();     
	}

	for(int i=0; i<=pos; i++) {
		std::cout << " ";
	}
	std::cout << "^" << std:: endl;

}

bool SDFReader::requestCommand(std::stringstream& line_stream) {
	std::string command;
	requestString(line_stream, command);

	if(command == "define") {
		requestDefinition(line_stream);
	} 
	if(command == "transform"){
		//std::cout<<"ERROR: "<<requestTransformation(line_stream)<<std::endl;
		requestTransformation(line_stream);
	}
	else {
		if(!error){
			int pos = line_stream.tellg();
			printError(line_stream, pos - command.size()-1, std::string("unknown command ") + command);
			return error;
		}
	}
	return !error;
};


bool SDFReader::requestString(std::stringstream& line_stream, std::string& str){
	int pos = line_stream.tellg();
	if(!(line_stream >> str)) {
		if(!error) {
			printError(line_stream, pos, std::string("expected string"));
		}
		error = true;
	}
	return !error;
};

bool SDFReader::requestDefinition(std::stringstream& line_stream){
	std::string entity_name;
	requestString(line_stream, entity_name);
	

	if(entity_name == "material") {
		requestMaterial(line_stream);

		// std::cout<<entity_name<<std::endl;
		// for (auto& x: materials) {
		// 	std::cout <<"SDF contains following Materials: "<<std::endl;
		// 	std::cout << x.first << ": " << *x.second << '\n';
		// }
	} 
	if(entity_name == "shape") {
		requestShape(line_stream);
	} 
	if(entity_name == "light"){
		requestLight(line_stream);
	}
	if(entity_name == "camera"){
		requestCamera(line_stream);
	}
	//weitere ifs


	else {
		int pos = line_stream.tellg();
		if(!error) {
			printError(line_stream, pos - entity_name.size()-1, std::string("unknown entity ") + entity_name);
		}
		error = true;
	}
	return !error;
};

bool SDFReader::requestTransformation(std::stringstream& line_stream){
	std::string item_name;
	requestString(line_stream, item_name);

	std::shared_ptr<Shape> shape_;
	std::map<std::string,std::shared_ptr<Shape>>::iterator it;
	it = shapes.find(item_name);
	if(it == shapes.end()){
		int pos = line_stream.tellg();
		printError(line_stream, pos - item_name.size()-1, std::string("transformation shape not found: ")+item_name);
		return error;
	}
	else{
		shape_ = shapes.find(item_name)->second;
	}

	std::string transformationType;
	requestString(line_stream, transformationType);

	if(transformationType == "scale"){
		requestScaling(line_stream, shape_);
	}
	if(transformationType == "translate"){
		requestTranslation(line_stream, shape_);
	}
	if(transformationType == "rotate"){
		requestRotation(line_stream, shape_);
	}
	else{
		int pos = line_stream.tellg();
		printError(line_stream, pos - transformationType.size()-1, std::string("transformation type unknown: ")+transformationType);
		return error;
	}
	return !error;
};

bool SDFReader::requestScaling(std::stringstream& line_stream, std::shared_ptr<Shape> const& shape){
	glm::vec3 scalingVector;
	requestVec3(line_stream, scalingVector);
	//TODO: Error ausgeben, wenn zu viele oder wenige Parameter gefunden werden?
	shape->scale(scalingVector);
	return !error;
};


bool SDFReader::requestTranslation(std::stringstream& line_stream, std::shared_ptr<Shape> const& shape){
	glm::vec3 translationVector;
	requestVec3 (line_stream, translationVector);
	//TODO: Error ausgeben, wenn zu viele oder wenige Parameter gefunden werden?
	shape->translate(translationVector);
	return !error;
};


bool SDFReader::requestRotation(std::stringstream& line_stream, std::shared_ptr<Shape> const& shape){
	float rotation_deg;
	requestFloat(line_stream, rotation_deg);

	glm::vec3 rotationAxis;
	requestVec3(line_stream, rotationAxis);

	shape->rotate(rotation_deg, rotationAxis);
	// std::cout<<"rotating: "<<rotation_deg<<"° at axis: "<<rotationAxis.x<<","<<rotationAxis.y<<","<<rotationAxis.z<<std::endl;
	return !error;
};

bool SDFReader::requestCamera(std::stringstream& line_stream){

//camera <name> <fov-x> <eye> <dir> <up>
	std::string camera_name;
	requestString(line_stream, camera_name);

	float fov_x;
	requestFloat(line_stream, fov_x);

	if(line_stream.eof()){
		Camera cam(fov_x);
		scene_.camera(cam);
		return !error;
	}

	glm::vec3 eye;
	requestVec3(line_stream, eye);

	glm::vec3 dir;
	requestVec3(line_stream, dir);

	glm::vec3 up;
	requestVec3(line_stream, up);


	Camera cam(fov_x,eye,dir,up);
	cameras.insert({camera_name,cam});

	return !error;
};

bool SDFReader::requestLight(std::stringstream& line_stream){

	std::string light_name;
	requestString(line_stream, light_name);

	glm::vec3 light_pos;
	requestVec3(line_stream,light_pos);

	Color diffuse;
	requestColor(line_stream,diffuse);

	Color ambient;
	requestColor(line_stream,ambient);

	Light l(light_pos,diffuse,ambient);
	scene_.add_light(l);
	lights.insert({light_name,l});

	return !error;
};

bool SDFReader::requestShape(std::stringstream& line_stream){

	int pos = 0; //current position

	std::string shapeType;
	requestString(line_stream, shapeType);

	if(shapeType == "box"){

		std::string name;
		requestString(line_stream, name);

		// std::cout<<shapeType<<" "<<name<<std::endl;

		glm::vec3 p1;
		requestVec3(line_stream, p1);
		 // std::cout<<p1.x<<","<<p1.y<<","<<p1.z<<std::endl;

		glm::vec3 p2;
		requestVec3(line_stream, p2);
		 // std::cout<<p1.x<<","<<p1.y<<","<<p1.z<<std::endl;


		std::string material_name;
		requestString(line_stream, material_name);
		std::shared_ptr<Material> mat = materials.find(material_name)->second;
		if(!mat){
			pos = line_stream.tellg();
			printError(line_stream, pos - material_name.size()-1, std::string("material not found: ")+material_name);
			return error;
		}

		auto shape = std::make_shared<Box>(mat);
		float xCenter = p2.x-(p2.x-p1.x)/2.0f;
		float yCenter = p2.y-(p2.y-p1.y)/2.0f;
		float zCenter = p2.z-(p2.z-p1.z)/2.0f;
		// std::cout<<"Center translation: "<<xCenter<<","<<yCenter<<","<<zCenter<<std::endl;
		shape->translate(glm::vec3(xCenter,yCenter,zCenter));

		float scalingX = glm::abs(p2.x-p1.x)/2.0f;
		float scalingY = glm::abs(p2.y-p1.y)/2.0f;
		float scalingZ = glm::abs(p2.z-p1.z)/2.0f;
		// std::cout<<"scaling: "<<scalingX<<","<<scalingY<<","<<scalingZ<<std::endl;

		shape->scale(glm::vec3(scalingX,scalingY,scalingZ));

		scene_.add_shape(shape); 
		shapes.insert ({name,shape});
	}
	if(shapeType == "sphere"){

		std::string name;
		requestString(line_stream, name);

		// std::cout<<shapeType<<" "<<name<<std::endl;

		glm::vec3 center;
		requestVec3(line_stream, center);

		float radius;
		requestFloat(line_stream, radius);

		std::string material_name;
		requestString(line_stream, material_name);
		std::shared_ptr<Material> mat = materials.find(material_name)->second;
		if(!mat){
			pos = line_stream.tellg();
			printError(line_stream, pos - material_name.size()-1, std::string("material not found: ")+material_name);
			return error;
		}

		auto shape = std::make_shared<Sphere>(mat);
		shape->translate(center);
		shape->scale(glm::vec3(glm::abs(radius)));
		scene_.add_shape(shape);
		shapes.insert ({name,shape});

	}
	if(shapeType == "composite"){
		std::string comp_name;
		requestString(line_stream, comp_name);
		auto comp = std::make_shared<Composite>();

		while(!line_stream.eof()){
			std::string child_name;
			requestString(line_stream, child_name);
			std::shared_ptr<Shape> child = shapes.find(child_name)->second;
			if(!child){
				pos = line_stream.tellg();
				printError(line_stream, pos - child_name.size()-1, std::string("child shape not found: ")+child_name);
				return error;
			}
			comp->add_child(child);
		}
	}

	else{
		if(!error) {
			pos = line_stream.tellg();
			printError(line_stream, pos - shapeType.size()-1, std::string("shapetype not found: ")+shapeType);
		}
		error = true;
	} 

	if(!line_stream.eof()) {
		if(!error) {
			pos = line_stream.tellg();
			printError(line_stream, pos, std::string("expected end of line"));
		}
		error = true;
	}

	return !error;
};

bool SDFReader::requestMaterial(std::stringstream& line_stream) {

	std::string name;
	requestString(line_stream, name);

	Color ambient;
	requestColor(line_stream, ambient);

	Color diffuse;
	requestColor(line_stream, diffuse);

	Color specular;
	requestColor(line_stream, specular);

	float m;
	requestFloat(line_stream, m);

	auto material = std::make_shared<Material>(ambient,diffuse,specular,m);
	materials.insert ({name,material});

	int pos = line_stream.tellg();
	if(!line_stream.eof()) {
		if(!error) {
			printError(line_stream, pos, std::string("expected end of line"));
		}
		error = true;
	}

	return !error;
};

bool SDFReader::requestFloat(std::stringstream& line_stream, float& f)
{
	int pos = line_stream.tellg();
	if(!(line_stream >> f)) {
		if(!error) {
			printError(line_stream, pos, std::string("expected float"));
		}
		error = true;
	}
	return !error;
}

bool SDFReader::requestVec3(std::stringstream& line_stream, glm::vec3& p)
{
	requestFloat(line_stream, p.x);
	requestFloat(line_stream, p.y);
	requestFloat(line_stream, p.z);
	return !error;
}

bool SDFReader::requestColor(std::stringstream& line_stream, Color& cl)
{
	requestFloat(line_stream, cl.r);
	requestFloat(line_stream, cl.g);
	requestFloat(line_stream, cl.b);
	return !error;
}
