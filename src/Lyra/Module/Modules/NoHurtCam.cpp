#include "NoHurtCam.hpp"
#include "../../SDK/SDK.hpp"

NoHurtCam::NoHurtCam() : ModuleCtor(67, "No Hurt Cam", "nohurtcam") {
	this->InitModuleSettings();
    originalCameraAngle.resize(5);
    memcpy(originalCameraAngle.data(), (LPVOID) sigOffset, 5);

}


std::string NoHurtCam::getModuleName() {
	return "No Hurt Cam";
}

void NoHurtCam::InitModuleSettings() {
	Settings::addSetting<bool>("No Hurt Cam", "enabled", false, true);
}

void NoHurtCam::onEnable() {
    if(!SDK::clientInstance || !SDK::clientInstance->getLocalPlayer()) return;
	Settings::getSettingByName<bool>("No Hurt Cam", "enabled")->value = true;
    eventMgr.addListener(this);

    originalCameraAngle.resize(1);
    memcpy(originalCameraAngle.data(), (LPVOID) sigOffset, 1);

	std::byte jump{0xEB};
    Memory::patchBytes((LPVOID) sigOffset, &jump, 1);
}

void NoHurtCam::onDisable() {
	Settings::getSettingByName<bool>("No Hurt Cam", "enabled")->value = false;
	eventMgr.removeListener(this);
    
    Memory::patchBytes((LPVOID) sigOffset, originalCameraAngle.data(), 1);
}