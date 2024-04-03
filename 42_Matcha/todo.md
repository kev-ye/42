[//]: # (Data begin: 31/05/2022)

Front: reactJs  
Back: Python Flask  
DB: postgresql

* Model:
> Global:
>> user { // database struct  
    id: int           -> primary key autoincrement  
    name: str         -> required & editable  
    fname: str        -> required & editable  
    birthday: date    -> optional & editable  
    sex: str          -> optional & editable  
    sex_o: str        -> optional & editable  
    tag_l: [str]      -> optional & editable  
    username: str     -> required & unique  
    password: str     -> required & editable  
    email: str        -> required & editable  
    location: str     -> optional & editable  
    bio: str          -> optional & editable  
    online: bool      -> optional  
    like_l: [str]     -> optional  
    consult_l: [str]  -> optional  
    black_l: [str]    -> optional  
    reported_l: [str] -> optional  
    image_l: [str]    -> optional  
  }  

> Auth:
> post: sign up
> post: sign in
> get: sign out
> payload {id + username}

> Profile:
> get & post: userinfo
> payload {bd, sex, sex_o, bio, tag, pic, email, password, fname, name, username, location}

> Match:
match {
  coming soon ...
}

> Chat:
chat {
  coming soon ...
}

> Notifications:
Notify {
  coming soon ...
}

* Routes - back:
> Authentication
>> - sign in       -> Post
>> - sign out      -> Post
>> - sign up       -> Post

> Profile
>> - get user      -> Get -> auth
>> - get like      -> Get -> auth
>> - get consult   -> Get -> auth
>> - get image     -> Get/Put -> auth
>> - update user   -> Put -> auth
>> - update user   -> Put -> no auth (use params?)

> Match / Research
>> - get suggest l -> Get -> auth
>> - get result l  -> Get -> auth

> Chat
>> - coming soon ...

> Notifications
>> - coming soon ...

- [ ] Sign up / in / out
  - [ ] pattern front & back
  * Sign up:
    - [ ] email
    - [ ] username
    - [ ] name
    - [ ] first name
    - [ ] password:
      - [ ] security
  * Sign in:
    - [ ] connect with username & password
    - [ ] reinitialize password with email
  
  * Sign out:
    - [ ] disconnect anywhere

- [ ] Profile
  - [ ] Edit:
    * editable information:
      - [ ] birthday
      - [ ] sex
      - [ ] sexual orientation
      - [ ] A short bio
      - [ ] A list of interests, in the form of tags (ex: #geek, #piercing, #vegan ...) These tags must be reusable
      - [ ] Pictures, maximum 5, including one serving as a profile photo
      - [ ] email
      - [ ] password
      - [ ] first name
      - [ ] location
    * Private information:
      - [ ] username
  - [ ] Be able to consult the people who have consulted / liked his profile
  - [ ] Popular score
  - [ ] Geolocate:
    - [ ] Default locate (if the uer does not want to be geolocated)
    - [ ] be able to modify his location on his profile

- [ ] Match
  - [ ] user need complete her public information (minimum 1: sexual orientation, location, interests, Popular score)
  - [ ] bisexual if sexual orientation doesn't set
  - [ ] criteria
    - [ ] sexual orientation
    - [ ] location
    - [ ] interests
    - [ ] Popular score
  - [ ] list of suggestions must be order by age, location, popular and common tags
  - [ ] criteria should be filterable by interval of:
    - [ ] age
    - [ ] location
    - [ ] popular
    - [ ] common tags

- [ ] Research
  - [ ] search with one or more criteria:
    - [ ] interval of age
    - [ ] interval of popular score
    - [ ] location
    - [ ] one or more interests tags
    - [ ] like match, it must be sortable and filterable by age, location, popular and tags

- [ ] Profile about others users
  - [ ] User must be able to consult the profile of other users:
    * birthday, sex, sexual orientation, bio, list of interests, first name, name, location
  - [ ] history of visits
  - [ ] User must be:
    - [ ] Like / Unlike others users: if they have minimum 1 picture
    - [ ] consult that the profile visited has already “liked” the user and can like it back
    - [ ] Consult popular score
    - [ ] Consult online stats, if offline, show last time of visit
    - [ ] report for fake account
    - [ ] black list:
      - [ ] never appear on result of research
      - [ ] no notification

- [ ] Chat
  - [ ] users matched can chat

- [ ] Notification
  - [ ] Anywhere
  - [ ] Like
  - [ ] Like back
  - [ ] Unlike
  - [ ] Visit
  - [ ] Message

- [ ] A seed test with 500 - 1000 profiles
