// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SKY_ENGINE_BINDINGS_FLUTTER_DART_STATE_H_
#define SKY_ENGINE_BINDINGS_FLUTTER_DART_STATE_H_

#include <string>

#include "dart/runtime/include/dart_api.h"
#include "lib/ftl/build_config.h"
#include "lib/tonic/dart_persistent_value.h"
#include "lib/tonic/dart_state.h"

namespace blink {

class DartJniIsolateData;
class MojoServices;

class IsolateClient {
 public:
  virtual void DidCreateSecondaryIsolate(Dart_Isolate isolate) = 0;

 protected:
  virtual ~IsolateClient();
};

class FlutterDartState : public tonic::DartState {
 public:
  FlutterDartState* CreateForChildIsolate();
  ~FlutterDartState() override;

  void DidSetIsolate() override;

  IsolateClient* isolate_client() { return isolate_client_; }

  static FlutterDartState* Current();

  Dart_Port main_port() const { return main_port_; }

  void set_mojo_services(std::unique_ptr<MojoServices> mojo_services);
  MojoServices* mojo_services();

#ifdef OS_ANDROID
  DartJniIsolateData* jni_data();
#endif

 protected:
  FlutterDartState(IsolateClient* isolate_client);

 private:
  IsolateClient* isolate_client_;

  Dart_Port main_port_;

  std::unique_ptr<MojoServices> mojo_services_;

#ifdef OS_ANDROID
  std::unique_ptr<DartJniIsolateData> jni_data_;
#endif
};

}  // namespace blink

#endif  // SKY_ENGINE_BINDINGS_FLUTTER_DART_STATE_H_
