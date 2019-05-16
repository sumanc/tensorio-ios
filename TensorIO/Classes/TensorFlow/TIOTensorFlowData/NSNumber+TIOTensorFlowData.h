//
//  NSNumber+TIOTensorFlowData.h
//  TensorIO
//
//  Created by Phil Dow on 4/10/19.
//  Copyright © 2019 doc.ai (http://doc.ai)
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

#import <Foundation/Foundation.h>
#import "TIOTensorFlowData.h"

namespace tensorflow {
    class Tensor;
}

NS_ASSUME_NONNULL_BEGIN

/**
 * An `NSNumber` can provide a single value to a TensorFlow tensor or accepts a
 * single value from a TensorFlow tensor.
 */

@interface NSNumber (TIOTensorFlowData) <TIOTensorFlowData>

/**
 * Initializes an `NSNumber` with bytes from a TensorFlow tensor.
 *
 * Bytes are copied according to the following rules, with information about quantization taken
 * from the description:
 *
 * - If the layer is unquantized, the tensor's bytes are copied directly into a numeric object
 *   (the dtype is used, or the bytes are implicitly interpreted as `float_t` values)
 *
 * - If the layer is quantized and no dequantizer block is provided, the tensor's bytes are copied
 *   directly into a numeric object (the bytes are implicitly interpreted as `uint8_t` values)
 *
 * - If the layer is quantized and a dequantizer block is provided, the tensor's bytes are
 *   interpreted as `uint8_t` values, passed to the dequantizer block, and the resulting `float_t`
 *   bytes are copied into a numeric object
 *
 * @param tensor The tensor to read from.
 * @param description A description of the data this tensor produces.
 *
 * @return instancetype An instance of `NSNumber`.
 */

- (nullable instancetype)initWithTensor:(tensorflow::Tensor)tensor description:(id<TIOLayerDescription>)description;

/**
 * Request to fill a TensorFlow tensor with bytes.
 *
 * Bytes are copied according to the following rules, with information about quantization taken
 * from the description:
 *
 * - If the layer is unquantized, the number's dtype value, or `float_t` by default, is copied
 *   directly to the tensor
 *
 * - If the layer is quantized and no quantizer block is provided, the number's `uint8_t` value is
 *   copied directly to the tensor
 *
 * - If the layer is quantized and a quantizer block is provided, the number's `float_t` vlaue
 *   is passed to the quantizer block and the `uint8_t` value it returns is copied to the tensor
 *
 * @param description A description of the data this tensor expects.
 *
 * @return tensorflow::Tensor A tensor with data from the number.
 */

- (tensorflow::Tensor)tensorWithDescription:(id<TIOLayerDescription>)description;

// MARK: - Batch (Training)

/**
 * Request to fill a TensorFlow tensor with bytes.
 *
 * Bytes are copied according to the following rules, with information about quantization taken
 * from the description:
 *
 * - If the layer is unquantized, the number's dtype value, or `float_t` by default, is copied
 *   directly to the tensor
 *
 * - If the layer is quantized and no quantizer block is provided, the number's `uint8_t` value is
 *   copied directly to the tensor
 *
 * - If the layer is quantized and a quantizer block is provided, the number's `float_t` vlaue
 *   is passed to the quantizer block and the `uint8_t` value it returns is copied to the tensor
 *
 * @param column A batch of numbers.
 * @param description A description of the data this tensor expects.
 *
 * @return tensorflow::Tensor A tensor with data from this batch of numbers.
 */

+ (tensorflow::Tensor)tensorWithColumn:(NSArray<id<TIOTensorFlowData>>*)column description:(id<TIOLayerDescription>)description;

@end

NS_ASSUME_NONNULL_END
