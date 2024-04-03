# Step 1: Dev
FROM node:17-alpine AS development

WORKDIR /camagru/back-end

COPY . .

RUN npm install

RUN npm run build

EXPOSE 3000

CMD [ "npm", "run", "serve" ]

# Step 2: Prod
FROM node:17-alpine AS product

ARG NODE_ENV=production
ENV NODE_ENV=production

WORKDIR /camagru/back-end

COPY . .

RUN npm install

COPY --from=development /camagru/back-end/dist ./dist

EXPOSE 3000

CMD [ "node", "dist/api" ]