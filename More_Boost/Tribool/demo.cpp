#include "Util/CK/CK.h"

#include <boost/logic/tribool.hpp>
	using boost::logic::tribool;
	using boost::logic::indeterminate;

int main() {

		/////////////////////////////////////////////////////////////////
CK_section(	"Negation    (!) ......."					)
		/////////////////////////////////////////////////////////////////

		tribool NOT_true= !tribool(true);
CK_compare(	indeterminate(NOT_true)				, false		)
CK_compare(	NOT_true					, false		)

		tribool NOT_false= !tribool(false);
CK_compare(	indeterminate(NOT_false)			, false		)
CK_compare(	NOT_false					, true		)

		tribool NOT_indeterminate= !tribool(indeterminate);
CK_compare(	indeterminate(NOT_indeterminate)		, true		)

		/////////////////////////////////////////////////////////////////
CK_section(	"Logical AND (&&) ......"					)
		/////////////////////////////////////////////////////////////////

		tribool false_AND_false= tribool(false)
				      && tribool(false);
CK_compare(	indeterminate(false_AND_false)			, false		)
CK_compare(	false_AND_false					, false		)

		tribool false_AND_true= tribool(false)
				     && tribool(true);
CK_compare(	indeterminate(false_AND_true)			, false		)
CK_compare(	false_AND_true					, false		)

		tribool true_AND_false= tribool(true)
				     && tribool(false);
CK_compare(	indeterminate(true_AND_false)			, false		)
CK_compare(	true_AND_false					, false		)

		tribool true_AND_true= tribool(true)
				    && tribool(true);
CK_compare(	indeterminate(true_AND_true)			, false		)
CK_compare(	true_AND_true					, true		)

		tribool false_AND_indeterminate= tribool(false)
					      && tribool(indeterminate);
CK_compare(	indeterminate(false_AND_indeterminate)		, false		)
CK_compare(	false_AND_indeterminate				, false		)

		tribool true_AND_indeterminate= tribool(true)
					     && tribool(indeterminate);
CK_compare(	indeterminate(true_AND_indeterminate)		, true		)

		tribool indeterminate_AND_false= tribool(indeterminate)
					      && tribool(false);
CK_compare(	indeterminate(indeterminate_AND_false)		, false		)
CK_compare(	indeterminate_AND_false				, false		)

		tribool indeterminate_AND_true= tribool(indeterminate)
					     && tribool(true);
CK_compare(	indeterminate(indeterminate_AND_true)		, true		)

		tribool indeterminate_AND_indeterminate= tribool(indeterminate)
						      && tribool(indeterminate);
CK_compare(	indeterminate(indeterminate_AND_indeterminate)	, true		)

		/////////////////////////////////////////////////////////////////
CK_section(	"Logical OR  (||) ......"					)
		/////////////////////////////////////////////////////////////////

		tribool false_OR_false= tribool(false)
				     || tribool(false);
CK_compare(	indeterminate(false_OR_false)			, false		)
CK_compare(	false_OR_false					, false		)

		tribool false_OR_true= tribool(false)
				    || tribool(true);
CK_compare(	indeterminate(false_OR_true)			, false		)
CK_compare(	false_OR_true					, true		)

		tribool true_OR_false= tribool(true)
				    || tribool(false);
CK_compare(	indeterminate(true_OR_false)			, false		)
CK_compare(	true_OR_false					, true		)

		tribool true_OR_true= tribool(true)
				   || tribool(true);
CK_compare(	indeterminate(true_OR_true)			, false		)
CK_compare(	true_OR_true					, true		)

		tribool false_OR_indeterminate= tribool(false)
					     || tribool(indeterminate);
CK_compare(	indeterminate(false_OR_indeterminate)		, true		)

		tribool true_OR_indeterminate= tribool(true)
					    || tribool(indeterminate);
CK_compare(	indeterminate(true_OR_indeterminate)		, false		)
CK_compare(	true_OR_indeterminate				, true		)

		tribool indeterminate_OR_false= tribool(indeterminate)
					     || tribool(false);
CK_compare(	indeterminate(indeterminate_OR_false)		, true		)

		tribool indeterminate_OR_true= tribool(indeterminate)
					    || tribool(true);
CK_compare(	indeterminate(indeterminate_OR_true)		, false		)
CK_compare(	indeterminate_OR_true				, true		)

		tribool indeterminate_OR_indeterminate= tribool(indeterminate)
						     || tribool(indeterminate);
CK_compare(	indeterminate(indeterminate_OR_indeterminate)	, true		)

		/////////////////////////////////////////////////////////////////
CK_section(	"Equality    (==) ......"					)
		/////////////////////////////////////////////////////////////////

		tribool false_EQ_false= tribool(false)
				     == tribool(false);
CK_compare(	indeterminate(false_EQ_false)			, false		)
CK_compare(	false_EQ_false					, true		)

		tribool false_EQ_true= tribool(false)
				    == tribool(true);
CK_compare(	indeterminate(false_EQ_true)			, false		)
CK_compare(	false_EQ_true					, false		)

		tribool true_EQ_false= tribool(true)
				    == tribool(false);
CK_compare(	indeterminate(true_EQ_false)			, false		)
CK_compare(	true_EQ_false					, false		)

		tribool true_EQ_true= tribool(true)
				   == tribool(true);
CK_compare(	indeterminate(true_EQ_true)			, false		)
CK_compare(	true_EQ_true					, true		)

		tribool false_EQ_indeterminate= tribool(false)
					     == tribool(indeterminate);
CK_compare(	indeterminate(false_EQ_indeterminate)		, true		)

		tribool true_EQ_indeterminate= tribool(true)
					    == tribool(indeterminate);
CK_compare(	indeterminate(true_EQ_indeterminate)		, true		)

		tribool indeterminate_EQ_false= tribool(indeterminate)
					     == tribool(false);
CK_compare(	indeterminate(indeterminate_EQ_false)		, true		)

		tribool indeterminate_EQ_true= tribool(indeterminate)
					    == tribool(true);
CK_compare(	indeterminate(indeterminate_EQ_true)		, true		)

		tribool indeterminate_EQ_indeterminate= tribool(indeterminate)
						     == tribool(indeterminate);
CK_compare(	indeterminate(indeterminate_EQ_indeterminate)	, true		)

		/////////////////////////////////////////////////////////////////
CK_section(	"Unequality  (!=) ......"					)
		/////////////////////////////////////////////////////////////////

		tribool false_NE_false= tribool(false)
				     != tribool(false);
CK_compare(	indeterminate(false_NE_false)			, false		)
CK_compare(	false_NE_false					, false		)

		tribool false_NE_true= tribool(false)
				    != tribool(true);
CK_compare(	indeterminate(false_NE_true)			, false		)
CK_compare(	false_NE_true					, true		)

		tribool true_NE_false= tribool(true)
				    != tribool(false);
CK_compare(	indeterminate(true_NE_false)			, false		)
CK_compare(	true_NE_false					, true		)

		tribool true_NE_true= tribool(true)
				   != tribool(true);
CK_compare(	indeterminate(true_NE_true)			, false		)
CK_compare(	true_NE_true					, false		)

		tribool false_NE_indeterminate= tribool(false)
					     != tribool(indeterminate);
CK_compare(	indeterminate(false_NE_indeterminate)		, true		)

		tribool true_NE_indeterminate= tribool(true)
					    != tribool(indeterminate);
CK_compare(	indeterminate(true_NE_indeterminate)		, true		)

		tribool indeterminate_NE_false= tribool(indeterminate)
					     != tribool(false);
CK_compare(	indeterminate(indeterminate_NE_false)		, true		)

		tribool indeterminate_NE_true= tribool(indeterminate)
					    != tribool(true);
CK_compare(	indeterminate(indeterminate_NE_true)		, true		)

		tribool indeterminate_NE_indeterminate= tribool(indeterminate)
						     != tribool(indeterminate);
CK_compare(	indeterminate(indeterminate_NE_indeterminate)	, true		)

}
