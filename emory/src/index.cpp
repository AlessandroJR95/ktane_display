#include "emory.h"
#include <napi.h>
#include <iostream>

std::vector<uintptr_t> getPointerOffsets(Napi::CallbackInfo& args) {
    std::vector<uintptr_t> pointsOffsets;

    for (int i = 2; i < args.Length(); i++) {
        pointsOffsets.push_back(GetPointerFromString(args[i].As<Napi::String>().Utf8Value().c_str()));
    }

    return pointsOffsets;
}

Napi::Number getFloatValueFrom(Napi::CallbackInfo& args) {
    Napi::Env env = args.Env();

    TCHAR* windowName = fromString(args[0].As<Napi::String>());
    TCHAR* moduleName = fromString(args[1].As<Napi::String>());

    DWORD pID;
    HANDLE pHandler = GetKtanePidAndProcess(windowName, &pID);
    uintptr_t baseAddress = GetModuleBaseAddress(moduleName, pID);
    
    return Napi::Number::New(env, GetFloatAddressValue(pHandler, baseAddress, getPointerOffsets(args)));
}

Napi::Number getIntValueFrom(Napi::CallbackInfo& args) {
    Napi::Env env = args.Env();

    TCHAR* windowName = fromString(args[0].As<Napi::String>());
    TCHAR* moduleName = fromString(args[1].As<Napi::String>());

    DWORD pID;
    HANDLE pHandler = GetKtanePidAndProcess(windowName, &pID);
    uintptr_t baseAddress = GetModuleBaseAddress(moduleName, pID);
    
    return Napi::Number::New(env, GetIntAddressValue(pHandler, baseAddress, getPointerOffsets(args)));
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(
        Napi::String::New(env, "getFloatValueFrom"),
        Napi::Function::New(env, getFloatValueFrom)
    );

    exports.Set(
        Napi::String::New(env, "getIntValueFrom"),
        Napi::Function::New(env, getIntValueFrom)
    );

    return exports;
}

NODE_API_MODULE(emory, Init);