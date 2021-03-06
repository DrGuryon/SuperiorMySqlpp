/*
 * Author: Tomas Nozicka
 */

#pragma once

#include <superior_mysqlpp/prepared_statements/validate_metadata_modes.hpp>


namespace SuperiorMySqlpp
{
    template<bool IsParamBinding, typename... Types>
    class Bindings;

    template<typename... Types>
    using ParamBindings = Bindings<true, Types...>;

    template<typename... Types>
    using ResultBindings = Bindings<false, Types...>;


    namespace detail
    {
        namespace PreparedStatementsDefault
        {
            constexpr auto getStoreResult()
            {
                return true;
            }

            constexpr auto getValidateMode()
            {
                return ValidateMetadataMode::ArithmeticPromotions;
            }

            constexpr auto getWarnMode()
            {
                return ValidateMetadataMode::Same;
            }
        }
    }

    template<typename ResultBindings, typename ParamBindings,
             bool storeResult=detail::PreparedStatementsDefault::getStoreResult(),
             ValidateMetadataMode validateMode=detail::PreparedStatementsDefault::getValidateMode(),
             ValidateMetadataMode warnMode=detail::PreparedStatementsDefault::getWarnMode()>
    class PreparedStatement;
}

