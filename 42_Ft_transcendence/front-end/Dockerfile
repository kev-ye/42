# Stage 1: build development image
FROM node:17-alpine AS development

WORKDIR /pong/front-end/

COPY . .

RUN npm install
RUN npm install -g @angular/cli
RUN npm audit fix --force

RUN npm run build

EXPOSE 4200

# Stage 2.1: build production - app image
FROM node:17-alpine AS production_dist

WORKDIR /pong/front-end

COPY . .

RUN npm install
RUN npm audit fix --force

RUN npm run build

# Stage 2.2: build production - nginx image
FROM nginx:alpine AS production

RUN rm -rf /usr/share/nginx/html/*

COPY --from=production_dist /pong/front-end/dist/front-end /usr/share/nginx/html
COPY --from=production_dist /pong/front-end/nginx/nginx.conf /etc/nginx/conf.d/default.conf

