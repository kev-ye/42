# Stage 1: build development image
FROM node:17-alpine AS development

WORKDIR /pong/back-end

#COPY package*.json ./
COPY . .

RUN npm install --force

RUN npm run build

EXPOSE 3000 3001 3002

# Stage 2: build production image
FROM node:17-alpine AS production

ARG NODE_ENV=production
ENV NODE_ENV=${NODE_ENV}

WORKDIR /pong/back-end

COPY . .

RUN npm install --force

COPY --from=development /pong/back-end/dist ./dist

EXPOSE 3000 3001 3002

# run app
CMD [ "node", "dist/main"]