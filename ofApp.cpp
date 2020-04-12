#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofFill();
	ofSetColor(39);

	ofTrueTypeFont font;
	font.loadFont("fonts/Kazesawa-Bold.ttf", 28, true, true, true);

	vector<string> word_list = { "sin", "cos", "noise" };
	for (const auto& word : word_list) {

		auto word_size = glm::vec2(font.stringWidth(word), font.stringHeight(word));
		auto path = font.getStringAsPoints(word, true, false);

		this->word_size_list.push_back(word_size);
		this->path_list.push_back(path);
	}
}
//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	for (int word_index = 0; word_index < this->word_size_list.size(); word_index++) {

		vector<glm::vec2> top_vertices, bottom_vertices;
		for (int x = 0; x <= 720; x += this->word_size_list[word_index].x * 1.05) {

			for (int path_index = 0; path_index < this->path_list[word_index].size(); path_index++) {

				auto outline = path_list[word_index][path_index].getOutline();

				ofBeginShape();
				for (int line_index = 0; line_index < outline.size(); line_index++) {

					if (line_index != 0) { ofNextContour(true); }

					auto vertices = outline[line_index].getVertices();
					for (int i = 0; i < vertices.size(); i++) {

						auto location = vertices[i] + glm::vec2(x, this->word_size_list[word_index].y * 0.5);
						auto y = 
							word_index == 0 ? ofMap(sin(location.x * 0.005 + ofGetFrameNum() * 0.025), -1, 1, 50, 670) :
							word_index == 1 ? ofMap(cos(location.x * 0.005 + ofGetFrameNum() * 0.025), -1, 1, 50, 670) : 
							ofMap(ofNoise(location.x * 0.005 + ofGetFrameNum() * 0.025), 0, 1, 50, 670);
						ofVertex(location + glm::vec2(0, y));
					}
				}
				ofEndShape(true);
			}
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}