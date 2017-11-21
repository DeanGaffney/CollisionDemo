#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	gui.setup();
	isRunning = false;
	reset();
}


void ofApp::reset() {
	t = T_MIN;
	v1 = v2 = u1 = u2 = ofVec2f::zero();
	m1 = m2 = 1.0f;
	c = 1.0f;
	p1 = p2 = ofVec3f::zero();
	d = (p1 - p2).normalize();
	closingVel = 0.0f;
	isRunning = false;
}

//--------------------------------------------------------------
void ofApp::update(){
	float dt = ofClamp(ofGetLastFrameTime(), 0.0, 0.02);

	if (isRunning && dt > 0.0f) {
		t += dt;
		if (t >= T_MAX) {
			isRunning = false;
			t = T_MIN;
		}
	}
	if (t < 0.0f) {
		p1 = t * v1;
		p2 = t * v2;
	}else {
		p1 = t * u1;
		p2 = t * u2;
	}

	u1 = ((m1 - c * m2) / (m1 + m2)) * v1 + ((m2 * (1 + c)) / (m1 + m2)) * v2;
	u2 = ((m1 * (1 + c)) / (m1 + m2)) * v1 + ((m2 - c * m1) / (m1 + m2)) * v2;

	d = (p1 - p2).normalize();
	closingVel = d.dot(v2 - v1);
}

//--------------------------------------------------------------
void ofApp::draw(){
	//render gui first
	gui.begin();
	drawMainWindow();
	gui.end();

	demoArea.x = mainWindowRectangle.getMaxX();
	demoArea.y = 0;
	demoArea.width = min((int)(ofGetWindowWidth() - demoArea.x), ofGetWindowHeight());
	demoArea.height = demoArea.width;
	
	ofPushMatrix();
	ofPushStyle();
		ofSetColor(0, 0, 255);
		ofTranslate(demoArea.x + demoArea.width / 2, demoArea.height / 2, 0);
		ofScale(demoArea.width / (2 * RANGE), -(demoArea.width / (2 * RANGE)), 1);
		ofNoFill();
		ofDrawRectangle(-RANGE, -RANGE, 2 * RANGE, 2 * RANGE);
		ofSetCircleResolution(80);
		for (int i = 0; i < 5; i++) {
			ofSetColor((i % 2 == 0) ? ofColor::black : ofColor::white);
			ofCircle(0, 0, i + 1);
		}
		ofFill();
		//particle 1 attributes
		ofSetColor(0, 0, 255);
		ofDrawCircle(p1.x, p1.y, RADIUS);
		ofSetColor(0, 200, 0);
		
		//particle 2 attributes
		ofSetColor(255, 0, 0);
		ofDrawCircle(p2.x, p2.y, RADIUS);
		ofSetColor(0, 200, 0);
		ofSetColor(0, 0, 255);
		ofPopStyle();
	ofPopMatrix();
}

void ofApp::drawMainWindow() {

	ImGui::SetNextWindowSize(ImVec2(200, 300), ImGuiSetCond_FirstUseEver);
	if (ImGui::Begin("Main")) {

		ImGui::Text("Particle 1:");

		ImGui::SliderFloat2("v1", &v1.x, -1.0f, 1.0f);
		ImGui::SliderFloat("m1", &m1, 1.0f, 100.0f);

		ImGui::Text("Particle 2:");

		ImGui::SliderFloat2("v2", &v2.x, -1.0f, 1.0f);
		ImGui::SliderFloat("m2", &m2, 1.0f, 100.0f);

		ImGui::SliderFloat("c", &c, 0.0f, 1.0f);

		if (ImGui::Button("Reset")) reset();
		ImGui::SameLine();
		if (ImGui::Button("Start")) t = T_MIN;
		ImGui::SameLine();
		if (ImGui::Button(isRunning ? "Stop" : " Go ")) {
			isRunning = !isRunning;
			if (isRunning && t == T_MAX) t = T_MIN;
		}
		if (ImGui::SliderFloat("Time", &t, T_MIN, T_MAX)) {
			//p1 = p1StartPos + v1 * t;
			//p2 = p2StartPos + v2 * t;
		}
		if (ImGui::Button("Quit")) quit();

		if (ImGui::CollapsingHeader("Numerical Output")) {
			ImGui::Text("d = (% 6.2f,% 6.2f) ", d.x, d.y);
			ImGui::Text("Closing Velocity = %.3f", closingVel);
			ImGui::Text("u1 = (% 6.2f,% 6.2f) ", u1.x, u1.y);
			ImGui::Text("u2 = (% 6.2f,% 6.2f) ", u2.x, u2.y);
			ImGui::Text("momentum = (% 6.2f,% 6.2f) ", momentum.x, momentum.y);
		}

		if (ImGui::CollapsingHeader("Tests")) {
			if (ImGui::Button("1D Elastic, p2 fixed (x-axis)")) {

			}
			if (ImGui::Button("1D Plastic, p2 fixed (x-axis)")) {

			}
			if (ImGui::Button("1D p2 fixed (x-axis) m1=H m2=L")) {

			}
			if (ImGui::Button("1D p2 fixed (x-axis) m1=L m2=H")) {

			}
			if (ImGui::Button("NW + SW Elastic")) {

			}
			if (ImGui::Button("NW + SW Plastic")) {

			}
		}
	}

	// store window size so that camera can ignore mouse clicks
	mainWindowRectangle.setPosition(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y);
	mainWindowRectangle.setSize(ImGui::GetWindowWidth(), ImGui::GetWindowHeight());
	ImGui::End();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::quit() {
	ofExit();
}
