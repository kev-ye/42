from flask import Blueprint
from flask_jwt_extended import jwt_required

import auth_utils as service

auth_bp = Blueprint('auth', __name__, url_prefix='/api/auth')


@auth_bp.route('/signup', methods=['POST'])
def sign_up():
	return service.handle_signup()


@auth_bp.route('/signin', methods=['POST'])
def sign_in():
	return service.handle_signin()


@auth_bp.route('/refresh', methods=['POST'])
@jwt_required()
def refresh_token():
	return service.handle_refresh()


@auth_bp.route('/islogin', methods=['GET'])
def is_login():
	return service.handle_is_login()
