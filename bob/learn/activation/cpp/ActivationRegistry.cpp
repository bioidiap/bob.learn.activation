/**
 * @author Andre Anjos <andre.anjos@idiap.ch>
 * @date Fri 17 May 2013 16:02:05 CEST
 *
 * @brief Implementation of the activation registry
 *
 * Copyright (C) Idiap Research Institute, Martigny, Switzerland
 */

#include <bob.learn.activation/Activation.h>

boost::shared_ptr<bob::learn::activation::ActivationRegistry> bob::learn::activation::ActivationRegistry::instance() {
  static boost::shared_ptr<bob::learn::activation::ActivationRegistry> s_instance(new ActivationRegistry());
  return s_instance;
}

void bob::learn::activation::ActivationRegistry::deregisterFactory(const std::string& id) {
  s_id2factory.erase(id);
}

void bob::learn::activation::ActivationRegistry::registerActivation(const std::string& id,
    bob::learn::activation::activation_factory_t factory) {

  auto it = s_id2factory.find(id);

  if (it == s_id2factory.end()) {
    s_id2factory[id] = factory;
  }
  else {
    if (s_id2factory[id] != factory) {
      boost::format m("replacing factory for activation functor `%s' with a different one is not allowed at this point");
      m % id;
      throw std::runtime_error(m.str());
    }
    //replacing with the same factory may be the result of multiple python
    //modules being loaded.
  }

}

bool bob::learn::activation::ActivationRegistry::isRegistered(const std::string& id) {
  return (s_id2factory.find(id) != s_id2factory.end());
}

bob::learn::activation::activation_factory_t bob::learn::activation::ActivationRegistry::find
(const std::string& id) {

  auto it = s_id2factory.find(id);

  if (it == s_id2factory.end()) {
    boost::format m("unregistered activation function: %s");
    m % id;
    throw std::runtime_error(m.str());
  }

  return it->second;

}

