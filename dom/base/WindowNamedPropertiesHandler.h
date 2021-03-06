/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=2 sw=2 et tw=78: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef mozilla_dom_WindowNamedPropertiesHandler_h
#define mozilla_dom_WindowNamedPropertiesHandler_h

#include "mozilla/dom/DOMJSProxyHandler.h"

namespace mozilla {
namespace dom {

class WindowNamedPropertiesHandler : public BaseDOMProxyHandler
{
public:
  MOZ_CONSTEXPR WindowNamedPropertiesHandler()
    : BaseDOMProxyHandler(nullptr, /* hasPrototype = */ true)
  {
  }
  virtual bool
  getOwnPropDescriptor(JSContext* aCx, JS::Handle<JSObject*> aProxy,
                       JS::Handle<jsid> aId,
                       bool /* unused */,
                       JS::MutableHandle<JSPropertyDescriptor> aDesc)
                       const override;
  virtual bool
  defineProperty(JSContext* aCx, JS::Handle<JSObject*> aProxy,
                 JS::Handle<jsid> aId,
                 JS::MutableHandle<JSPropertyDescriptor> aDesc,
                 JS::ObjectOpResult &result) const override;
  virtual bool
  ownPropNames(JSContext* aCx, JS::Handle<JSObject*> aProxy, unsigned flags,
               JS::AutoIdVector& aProps) const override;
  virtual bool
  delete_(JSContext* aCx, JS::Handle<JSObject*> aProxy, JS::Handle<jsid> aId,
          JS::ObjectOpResult &aResult) const override;
  virtual bool
  preventExtensions(JSContext* aCx, JS::Handle<JSObject*> aProxy,
                    JS::ObjectOpResult& aResult) const override
  {
    return aResult.failCantPreventExtensions();
  }
  virtual bool
  isExtensible(JSContext* aCx, JS::Handle<JSObject*> aProxy,
               bool* aIsExtensible) const override
  {
    *aIsExtensible = true;
    return true;
  }
  virtual const char*
  className(JSContext *aCx, JS::Handle<JSObject*> aProxy) const override
  {
    return "WindowProperties";
  }

  static const WindowNamedPropertiesHandler*
  getInstance()
  {
    static const WindowNamedPropertiesHandler instance;
    return &instance;
  }

  // For Create, aProto is the parent of the interface prototype object of the
  // Window we're associated with.
  static JSObject*
  Create(JSContext *aCx, JS::Handle<JSObject*> aProto);
};

} // namespace dom
} // namespace mozilla

#endif /* mozilla_dom_WindowNamedPropertiesHandler_h */
