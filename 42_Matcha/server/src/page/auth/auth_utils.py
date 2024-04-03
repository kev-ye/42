from flask import request
from flask_jwt_extended import (
	create_access_token,
	create_refresh_token,
	get_jwt_identity
)
from werkzeug.security import check_password_hash

from common.utils import msg_response
from common.database import insert_one, find_one


# restful

# post: sign up logic
def handle_signup():
	data = request.get_json(force=True, silent=True)
	response = msg_response('signup failed', 401)

	if find_one('users', 'username', ['username']) is not None:
		return msg_response('Username already use', 401)

	return msg_response('signup success', 200) \
		if insert_one('users', data) is True else response


# post: sign in logic
def handle_signin():
	data = request.get_json(force=True, silent=True)
	user = find_one('users', 'username', data['username'])

	if user is None:
		return msg_response('username invalid', 401)
	elif not check_password_hash(user['password'], data['password']):
		return msg_response('password invalid', 401)

	access_token = create_access_token(identity={
		"id": user['id'],
		"username": user['username']
	})
	refresh_token = create_refresh_token(identity={
		"id": user['id'],
		"username": user['username']
	})
	return {
		"access_token": access_token,
		"refresh_token": refresh_token
	}


# get: check if is login
def handle_is_login():
	return True


# post: refresh token
def handle_refresh():
	identity = get_jwt_identity()
	access_token = create_access_token(identity)
	return {"access_token": access_token}
