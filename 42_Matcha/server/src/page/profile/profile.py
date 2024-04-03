from flask import Blueprint, request
from flask_jwt_extended import jwt_required

import profile_utils as service

profile_bp = Blueprint('profile', __name__, url_prefix='/api/profile')


@profile_bp.route('/profile', methods=['GET', 'POST'])
@jwt_required()
def profile():
	if request.method == 'POST':
		return service.update_user_info()
	return service.get_user_info()


@profile_bp.route('/profile/<param>', methods=['GET', 'POST'])
@jwt_required()
def profile_info(param):
	return service.get_user_info_params(param)
