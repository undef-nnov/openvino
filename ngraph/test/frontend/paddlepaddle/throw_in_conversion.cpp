// Copyright (C) 2018-2021 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#include <common/frontend_exceptions.hpp>
#include <manager.hpp>

#include "common_test_utils/ngraph_test_utils.hpp"
#include "paddle_utils.hpp"
#include "utils.hpp"

using namespace ngraph;
using namespace ov::frontend;

TEST(FrontEndConvertModelTest, throw_in_conversion) {
    FrontEndManager fem;
    FrontEnd::Ptr frontEnd;
    InputModel::Ptr inputModel;
    ASSERT_NO_THROW(frontEnd = fem.load_by_framework(PADDLE_FE));
    ASSERT_NE(frontEnd, nullptr);
    auto model_filename = FrontEndTestUtils::make_model_path(
        std::string(TEST_PADDLE_MODELS_DIRNAME) + std::string("throw_in_conversion/throw_in_conversion.pdmodel"));
    ASSERT_NO_THROW(inputModel = frontEnd->load(model_filename));
    ASSERT_NE(inputModel, nullptr);
    std::shared_ptr<ngraph::Function> function;
    ASSERT_THROW(function = frontEnd->convert(inputModel), OpConversionFailure);
}

TEST(FrontEndConvertModelTest, unsupported_version) {
    FrontEndManager fem;
    FrontEnd::Ptr frontEnd;
    InputModel::Ptr inputModel;
    ASSERT_NO_THROW(frontEnd = fem.load_by_framework(PADDLE_FE));
    ASSERT_NE(frontEnd, nullptr);
    auto model_filename = FrontEndTestUtils::make_model_path(std::string(TEST_PADDLE_MODELS_DIRNAME) +
                                                             std::string("lower_version/lower_version.pdmodel"));

    ASSERT_THROW(inputModel = frontEnd->load(model_filename), GeneralFailure);
}
