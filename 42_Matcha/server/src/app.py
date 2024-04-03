import os
from datetime import timedelta

from flask import Flask
from flask_jwt_extended import JWTManager
from flask_cors import CORS

import config
import db_init

from page.auth import auth
from page.profile import profile


app = Flask(__name__)
CORS(app)

app.config.from_mapping(
    JWT_COOKIE_SECURE=False,
    JWT_SECRET_KEY=config.JWT_SECRET_KEY,
    JWT_ACCESS_TOKEN_EXPIRES=timedelta(hours=1),
    JWT_REFRESH_TOKEN_EXPIRES=timedelta(days=30)
)

# init db
db_init.init_app(app)

# init jwt
jwt = JWTManager(app)

# blueprint
app.register_blueprint(auth.auth_bp)
app.register_blueprint(profile.profile_bp)

