# Step 1: Dev
FROM node:17-alpine AS development

WORKDIR /camagru/front-end

COPY . .

RUN npm install

EXPOSE 5050

CMD [ "node", "front.server.js" ]

# Step 2: Prod
FROM nginx:alpine AS product

RUN rm -rf /usr/share/nginx/html/*

COPY --from=development /camagru/front-end/ /usr/share/nginx/html/
COPY --from=development /camagru/front-end/nginx/default.conf /etc/nginx/conf.d/default.conf

EXPOSE 8080

CMD [ "nginx", "-g", "\"daemon off;\"" ]