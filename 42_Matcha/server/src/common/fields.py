from flask_restful import fields


# should be consulted by self or username
userinfo_limit = {
	"username": fields.String(),
	"name": fields.String(),
	"fname": fields.String(),
	"birthday": fields.DateTime(),
	"sex": fields.String(),
	"sex_o": fields.String(),
	"bio": fields.String(),
	"online": fields.DateTime(),
	"location": fields.String(),
	"like_l": fields.List(fields.String()),
	"tag_l": fields.List(fields.String()),
	"image_l": fields.List(fields.String())
}

# should be consulted by self
userinfo_history = {
	"like_l": fields.List(fields.String()),
	"consult_l": fields.List(fields.String())
}

# should be consulted by self
userinfo_black_list = {
	"black_l": fields.List(fields.String())
}

# should be consulted by username
userinfo_reported_list = {
	"reported_l": fields.List(fields.String())
}