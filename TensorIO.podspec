#
# Be sure to run `pod lib lint TensorIO.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see https://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = 'TensorIO'
  s.version          = '0.9.7'
  s.summary          = 'An Objective-C and Swift wrapper for TensorFlow Lite and TensorFlow, with support for Federated Learning.'
  s.description      = 'Perform inference with TensorFlow Lite or full TensorFlow models using all the conveniences of Objective-C or Swift'
  s.homepage         = 'https://github.com/doc-ai/tensorio-ios'
  s.license          = { :type => 'Apache 2', :file => 'LICENSE' }
  s.authors          = { 'doc.ai' => 'philip@doc.ai' }
  s.source           = { :git => 'https://github.com/doc-ai/tensorio-ios.git', :tag => s.version.to_s }

  s.ios.deployment_target = '12.0'
  s.static_framework = true
  
  s.frameworks = 'Foundation', 'UIKit', 'AVFoundation', 'CoreGraphics', 'CoreMedia', 'CoreVideo', 'Accelerate', 'VideoToolbox'
  s.library = 'c++'
  
  s.dependency 'DSJSONSchemaValidation'
  
  s.default_subspec = 'Core'
  
  # Core subspec contains base classes and protocol definitions but no model implementation
  
  s.subspec 'Core' do |ss|
    ss.source_files = 'TensorIO/Classes/Core/**/*'
    ss.pod_target_xcconfig = {
      'GCC_PREPROCESSOR_DEFINITIONS' => "TIO_CORE=1 TIO_VERSION=#{s.version}"
    }
  end
  
  # TFLite subspec contains the TensorFlow Lite implementation
  
  s.subspec 'TFLite' do |ss|
    ss.dependency 'TensorIO/Core'
    ss.dependency 'TensorFlowLite'
    
    ss.source_files = 'TensorIO/Classes/TFLite/**/*'
    ss.private_header_files = [
      'TensorIO/Classes/TFLite/TIOTFLiteData/**/*.h'
    ]
    ss.resource_bundles = { 
      'TFLite' => 'TensorIO/Assets/TFLite/**/*' 
    }
    ss.xcconfig = {
      'USER_HEADER_SEARCH_PATHS' => '"${PODS_ROOT}/TensorFlowLite/Frameworks/tensorflow_lite.framework/Headers"'
    }
    ss.pod_target_xcconfig = {
      'GCC_PREPROCESSOR_DEFINITIONS' => 'TIO_TFLITE=1'
    }
  end
  
  # TensorFlow subspec contains a full TensorFlow implementation

  s.subspec 'TensorFlow' do |ss|
    ss.dependency 'TensorIO/Core'
    ss.dependency 'TensorIOTensorFlow'

    ss.source_files = 'TensorIO/Classes/TensorFlow/**/*'
    ss.private_header_files = [
      'TensorIO/Classes/TensorFlow/SavedModel/**/*.h',
      'TensorIO/Classes/TensorFlow/TIOTensorFlowData/**/*.h'
    ]
    ss.resource_bundles = { 
      'TensorFlow' => 'TensorIO/Assets/TensorFlow/**/*' 
    }
    ss.xcconfig = {
      'HEADER_SEARCH_PATHS' => '"${PODS_ROOT}/TensorIOTensorFlow/Frameworks/tensorflow.framework/Headers"',
      'OTHER_LDFLAGS' => '-force_load "${PODS_ROOT}/TensorIOTensorFlow/Frameworks/tensorflow.framework/tensorflow" "-L ${PODS_ROOT}/TensorIOTensorFlow/Frameworks/tensorflow.framework"'
    }
    ss.pod_target_xcconfig = {
      'GCC_PREPROCESSOR_DEFINITIONS' => 'TIO_TENSORFLOW=1'
    }
  end

end
