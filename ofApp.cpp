#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	auto ico_sphere = ofIcoSpherePrimitive(250, 5);
	this->triangle_list.insert(this->triangle_list.end(), ico_sphere.getMesh().getUniqueFaces().begin(), ico_sphere.getMesh().getUniqueFaces().end());
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();

	ofSeedRandom(39);

	auto noise_seed = ofRandom(1000);
	for (int k = 0; k < this->triangle_list.size(); k++) {

		glm::vec3 avg = (this->triangle_list[k].getVertex(0) + this->triangle_list[k].getVertex(1) + this->triangle_list[k].getVertex(2)) / 3;

		vector<glm::vec3> vertices;
		vertices.push_back(this->triangle_list[k].getVertex(0));
		vertices.push_back(this->triangle_list[k].getVertex(1));
		vertices.push_back(this->triangle_list[k].getVertex(2));

		for (int i = 0; i < 4; i++) {

			for (auto& v : vertices) {

				auto rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(v * 0.002, ofGetFrameNum() * 0.02)), 0, 1, -120, 120) * (float)DEG_TO_RAD, glm::vec3(1, 0, 0));
				auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(v * 0.002, ofGetFrameNum() * 0.02)), 0, 1, -120, 120) * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
				auto rotation_z = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(v * 0.002, ofGetFrameNum() * 0.02)), 0, 1, -120, 120) * (float)DEG_TO_RAD, glm::vec3(0, 0, 1));
				v = glm::vec4(v, 0) * rotation_z * rotation_y * rotation_x;
			}
		}

		this->mesh.addVertices(vertices);

		ofColor color;
		color.setHsb(ofMap(k, 0, this->triangle_list.size(), 0, 255), 255, 255);
		for (int i = 0; i < 4; i++) {

			this->mesh.addColor(ofColor(color, 16));
		}

		this->mesh.addTriangle(this->mesh.getNumVertices() - 1, this->mesh.getNumVertices() - 2, this->mesh.getNumVertices() - 3);

	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 2.88);

	this->mesh.drawWireframe();

	this->cam.end();

	/*
	int start = 150;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}


//--------------------------------------------------------------
int main() {
	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}