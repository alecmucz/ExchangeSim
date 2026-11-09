FROM eclipse-temurin:25-jdk AS build
WORKDIR /src

COPY gradlew settings.gradle.kts build.gradle.kts ./
COPY gradle ./gradle
RUN ./gradlew dependencies --no-daemon > /dev/null

COPY src ./src
RUN ./gradlew bootJar -x test --no-daemon

FROM eclipse-temurin:25-jre
WORKDIR /app
RUN useradd --system app
COPY --from=build /src/build/libs/app.jar app.jar
USER app
EXPOSE 8080
ENTRYPOINT ["java", "-jar", "app.jar"]