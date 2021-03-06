#pragma once

#include "watch.h"

#include <QtCore/QString>
#include <QtCore/QVariant>

class Param
{
public:
	Param(int i_type, const QString & i_name, const QString & i_label, const QString & i_tip, int i_min = -1, int i_max = -1);
	~Param();

	enum Type {
		TInt = 0,
		TStr = 1,
		TReg = 2,
		Time = 3
	};

	const int type;
	const QString name;
	const QString label;
	const QString tip;
	const int min;
	const int max;

	// Convert variable to string.
	// Default is true if value is default,
	// as default parameters can be hidden.
	const QString varToQStr(const QVariant & i_var, bool * o_default = NULL) const;
};

