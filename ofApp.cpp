#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	gui.setup();
	isRunning = false;
	reset();

	fill(distanceLine.begin(), distanceLine.end(), 0.0f);
	fill(closingVelLine.begin(), closingVelLine.end(), 0.0f);
}


void ofApp::reset() {
	t = 0.0f;
	p1StartPos = p1Pos = p1Vel = ofVec3f::zero();
	p2StartPos = p2Pos = ofVec3f(3, 3, 0);
	p2Vel = ofVec3f::zero();
	distanceVector = (p1Pos - p2Pos).normalize();
	closingVel = 0.0f;
	isRunning = false;
	distanceLine.clear();
	closingVelLine.clear();
}


//--------------------------------------------------------------
void ofApp::update(){
	float dt = ofClamp(ofGetLastFrameTime(), 0.0, 0.02);

	if (isRunning && dt > 0.0f) {
		t += dt;
		p1Pos += dt * p1Vel;
		p2Pos += dt * p2Vel;
		distanceLine.insert(distanceLine.begin(), distanceVector.x);
		closingVelLine.insert(closingVelLine.begin(), closingVel);
	}
	if (t >= MAX_TIME) isRunning = false;

	distanceVector = (p1Pos - p2Pos).normalize();
	closingVel = distanceVector.dot(p2Vel - p1Vel);
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
		ofFill();
		//particle 1 attributes
		ofSetColor(0, 0, 255);
		ofDrawCircle(p1Pos.x, p1Pos.y, RADIUS);
		ofSetColor(0, 200, 0);
		ofDrawArrow(p1Pos, p1Pos + p1Vel);		//velocity arrow
		
		//particle 2 attributes
		ofSetColor(0, 0, 255);
		ofDrawCircle(p2Pos.x, p2Pos.y, RADIUS);
		ofSetColor(0, 200, 0);
		ofDrawArrow(p2Pos, p2Pos + p2Vel);		//velocity arrow
		ofSetColor(0, 0, 255);
		ofDrawArrow(p2Pos, p2Pos + (p1Pos - p2Pos).getNormalized());		//direction arrow
		ofPopStyle();
	ofPopMatrix();
}

void ofApp::drawMainWindow() {

	ImGui::SetNextWindowSize(ImVec2(200, 300), ImGuiSetCond_FirstUseEver);
	if (ImGui::Begin("Main")) {

		if (ImGui::Button("Reset")) reset();
		ImGui::SameLine();
		if (ImGui::Button(isRunning ? "Stop" : " Go ")) isRunning = !isRunning;
		ImGui::SameLine();
		ImGui::Text("   Time = %8.1f", t);
		if (ImGui::Button("Quit")) quit();

		ImGui::SliderFloat2("P1Pos", &p1Pos.x, -5.0f, 5.0f);
		ImGui::SliderFloat2("P1Vel", &p1Vel.x, -1.0f, 1.0f);

		ImGui::SliderFloat2("P2Pos", &p2Pos.x, -5.0f, 5.0f);
		ImGui::SliderFloat2("P2Vel", &p2Vel.x, -1.0f, 1.0f);

		ImGui::Text("Distance Vec = (% 6.2f,% 6.2f) ", distanceVector.x, distanceVector.y);
		ImGui::Text("Closing Velocity = %.3f", closingVel);

		if (ImGui::SliderFloat("Time", &t, 0.0f, 10.0f)) {
			p1Pos = p1StartPos + p1Vel * t;
			p2Pos = p2StartPos + p2Vel * t;
			distanceLine.clear();
			closingVelLine.clear();
		}

		if (ImGui::CollapsingHeader("Graphs")) {
			if(!distanceLine.empty())ImGui::PlotLines("Distance (x)", &distanceLine[0], distanceLine.size());
			if(!closingVelLine.empty())ImGui::PlotLines("Closing Velocity", &closingVelLine[0], closingVelLine.size());
		}
	}

	ImGui::SetWindowSize(ImVec2(0, 0));

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
