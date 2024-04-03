from flask import request, make_response
from flask_jwt_extended import get_jwt_identity, verify_jwt_in_request

from common.fields import (
	userinfo_limit,
	userinfo_history,
	userinfo_black_list,
	userinfo_reported_list
)
from common.database import find_one, update_one


# restful

# get: get user public information
def get_user_info():
	identity, data = _common_data()

	if data is None:
		return _result(
			identity['username'] if 'username' in identity else None,
			userinfo_limit
		)
	return _result(
		data['username'] if 'username' in data else None,
		userinfo_limit
	)


# get: get user information with params
def get_user_info_params(param):
	params = {
		'history': _common_result(get_jwt_identity(), userinfo_history),
		'black_list': _common_result(get_jwt_identity(), userinfo_black_list),
		'reported_list': _common_result(request.get_json(force=True, silent=True), userinfo_reported_list)
	}

	if param is not None:
		for k, v in params.items():
			if k == param:
				return v

	return msg_response('invalid params', 400)


# post: update user info
def update_user_info():
	identity, data = _common_data()
	response = msg_response('invalid data', 400)
	key_filter = ['id', 'username']

	for key in key_filter:
		if key in data:
			return response

	update = update_one(
		'users',
		data,
		'id',
		identity['id'] if 'id' in identity else None
	)

	return msg_response('update success', 200)\
		if update is True else response


# utils

# private: jwt payload & request json data
def _common_data():
	return get_jwt_identity(), request.get_json(force=True, silent=True)


# private: common result
def _common_result(data: dict, fields_obj: dict):
	response = msg_response('user invalid', 400)

	return _result(data['username'], fields_obj)\
		if data is not None and 'username' in data else response


# private: result filtered by fields
def _result(username: str, fields_obj: dict):
	user_data = find_one('users', 'username', username)

	return msg_response('user invalid', 400)\
		if user_data is None else make_response(marshal(user_data, fields_obj), 200)

