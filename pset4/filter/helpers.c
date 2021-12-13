#include "helpers.h"
#include <stdlib.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; ++h) {
        for (int w = 0; w < width; ++w) {
            BYTE avg = round((image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed) / 3.);
            image[h][w].rgbtBlue = image[h][w].rgbtGreen = image[h][w].rgbtRed = avg;
        }
    }
}

static double limit(double a) {
    if (a > 255) return 255;
    if (a < 0) return 0;
    return a;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; ++h) {
        for (int w = 0; w < width; ++w) {
            int originalBlue = image[h][w].rgbtBlue;
            int originalGreen = image[h][w].rgbtGreen;
            int originalRed = image[h][w].rgbtRed;
            image[h][w].rgbtBlue = limit(round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue));
            image[h][w].rgbtGreen = limit(round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue));
            image[h][w].rgbtRed = limit(round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue));
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; ++h) {
        for (int w = 0; w < width / 2; ++w) {
            RGBTRIPLE tmp = image[h][w];
            image[h][w] = image[h][width - 1 - w];
            image[h][width - 1 - w] = tmp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE** originalImage = (RGBTRIPLE**) malloc(sizeof(RGBTRIPLE*) * height);
    for (int i = 0; i < height; ++i) {
        originalImage[i] = (RGBTRIPLE*) malloc(sizeof(RGBTRIPLE) * width);
        for (int j = 0; j < width; ++j) {
            originalImage[i][j] = image[i][j];
        }
    }

    // center
    for (int i = 1; i < height - 1; ++i) {
        for (int j = 1; j < width - 1; ++j) {
            image[i][j].rgbtBlue = round((
                originalImage[i - 1][j - 1].rgbtBlue + originalImage[i - 1][j].rgbtBlue + originalImage[i - 1][j + 1].rgbtBlue +
                originalImage[i][j - 1].rgbtBlue + originalImage[i][j].rgbtBlue + originalImage[i][j + 1].rgbtBlue +
                originalImage[i + 1][j - 1].rgbtBlue + originalImage[i + 1][j].rgbtBlue + originalImage[i + 1][j + 1].rgbtBlue
            ) / 9.);
            image[i][j].rgbtGreen = round((
                originalImage[i - 1][j - 1].rgbtGreen + originalImage[i - 1][j].rgbtGreen + originalImage[i - 1][j + 1].rgbtGreen +
                originalImage[i][j - 1].rgbtGreen + originalImage[i][j].rgbtGreen + originalImage[i][j + 1].rgbtGreen +
                originalImage[i + 1][j - 1].rgbtGreen + originalImage[i + 1][j].rgbtGreen + originalImage[i + 1][j + 1].rgbtGreen
            ) / 9.);
            image[i][j].rgbtRed = round((
                originalImage[i - 1][j - 1].rgbtRed + originalImage[i - 1][j].rgbtRed + originalImage[i - 1][j + 1].rgbtRed +
                originalImage[i][j - 1].rgbtRed + originalImage[i][j].rgbtRed + originalImage[i][j + 1].rgbtRed +
                originalImage[i + 1][j - 1].rgbtRed + originalImage[i + 1][j].rgbtRed + originalImage[i + 1][j + 1].rgbtRed
            ) / 9.);
        }
    }
    // four edges
    if (height > 1) for (int i = 1; i < width - 1; ++i) {
        image[0][i].rgbtBlue = round((originalImage[0][i - 1].rgbtBlue + originalImage[0][i].rgbtBlue + originalImage[0][i + 1].rgbtBlue +
                originalImage[1][i - 1].rgbtBlue + originalImage[1][i].rgbtBlue + originalImage[1][i + 1].rgbtBlue) / 6.);
        image[height - 1][i].rgbtBlue = round((originalImage[height - 1][i - 1].rgbtBlue + originalImage[height - 1][i].rgbtBlue + originalImage[height - 1][i + 1].rgbtBlue +
                originalImage[height - 2][i - 1].rgbtBlue + originalImage[height - 2][i].rgbtBlue + originalImage[height - 2][i + 1].rgbtBlue) / 6.);
        image[0][i].rgbtGreen = round((originalImage[0][i - 1].rgbtGreen + originalImage[0][i].rgbtGreen + originalImage[0][i + 1].rgbtGreen +
                originalImage[1][i - 1].rgbtGreen + originalImage[1][i].rgbtGreen + originalImage[1][i + 1].rgbtGreen) / 6.);
        image[height - 1][i].rgbtGreen = round((originalImage[height - 1][i - 1].rgbtGreen + originalImage[height - 1][i].rgbtGreen + originalImage[height - 1][i + 1].rgbtGreen +
                originalImage[height - 2][i - 1].rgbtGreen + originalImage[height - 2][i].rgbtGreen + originalImage[height - 2][i + 1].rgbtGreen) / 6.);
        image[0][i].rgbtRed = round((originalImage[0][i - 1].rgbtRed + originalImage[0][i].rgbtRed + originalImage[0][i + 1].rgbtRed +
                originalImage[1][i - 1].rgbtRed + originalImage[1][i].rgbtRed + originalImage[1][i + 1].rgbtRed) / 6.);
        image[height - 1][i].rgbtRed = round((originalImage[height - 1][i - 1].rgbtRed + originalImage[height - 1][i].rgbtRed + originalImage[height - 1][i + 1].rgbtRed +
                originalImage[height - 2][i - 1].rgbtRed + originalImage[height - 2][i].rgbtRed + originalImage[height - 2][i + 1].rgbtRed) / 6.);
    }
    if (width > 1) for (int i = 1; i < height - 1; ++i) {
        image[i][0].rgbtBlue = round((originalImage[i - 1][0].rgbtBlue + originalImage[i][0].rgbtBlue + originalImage[i + 1][0].rgbtBlue +
                originalImage[i - 1][1].rgbtBlue + originalImage[i][1].rgbtBlue + originalImage[i + 1][1].rgbtBlue) / 6.);
        image[i][width - 1].rgbtBlue = round((originalImage[i - 1][width - 1].rgbtBlue + originalImage[i][width - 1].rgbtBlue + originalImage[i + 1][width - 1].rgbtBlue +
                originalImage[i - 1][width - 2].rgbtBlue + originalImage[i][width - 2].rgbtBlue + originalImage[i + 1][width - 2].rgbtBlue) / 6.);
        image[i][0].rgbtGreen = round((originalImage[i - 1][0].rgbtGreen + originalImage[i][0].rgbtGreen + originalImage[i + 1][0].rgbtGreen +
                originalImage[i - 1][1].rgbtGreen + originalImage[i][1].rgbtGreen + originalImage[i + 1][1].rgbtGreen) / 6.);
        image[i][width - 1].rgbtGreen = round((originalImage[i - 1][width - 1].rgbtGreen + originalImage[i][width - 1].rgbtGreen + originalImage[i + 1][width - 1].rgbtGreen +
                originalImage[i - 1][width - 2].rgbtGreen + originalImage[i][width - 2].rgbtGreen + originalImage[i + 1][width - 2].rgbtGreen) / 6.);
        image[i][0].rgbtRed = round((originalImage[i - 1][0].rgbtRed + originalImage[i][0].rgbtRed + originalImage[i + 1][0].rgbtRed +
                originalImage[i - 1][1].rgbtRed + originalImage[i][1].rgbtRed + originalImage[i + 1][1].rgbtRed) / 6.);
        image[i][width - 1].rgbtRed = round((originalImage[i - 1][width - 1].rgbtRed + originalImage[i][width - 1].rgbtRed + originalImage[i + 1][width - 1].rgbtRed +
                originalImage[i - 1][width - 2].rgbtRed + originalImage[i][width - 2].rgbtRed + originalImage[i + 1][width - 2].rgbtRed) / 6.);
    }
    // four corners
    if (width > 1 && height > 1) {
        image[0][0].rgbtBlue = round((originalImage[0][0].rgbtBlue + originalImage[0][1].rgbtBlue + originalImage[1][0].rgbtBlue + originalImage[1][1].rgbtBlue) / 4.);
        image[height - 1][0].rgbtBlue = round((originalImage[height - 1][0].rgbtBlue + originalImage[height - 2][0].rgbtBlue + originalImage[height - 1][1].rgbtBlue + originalImage[height - 2][1].rgbtBlue) / 4.);
        image[0][width - 1].rgbtBlue = round((originalImage[0][width - 1].rgbtBlue + originalImage[1][width - 1].rgbtBlue + originalImage[0][width - 2].rgbtBlue + originalImage[1][width - 2].rgbtBlue) / 4.);
        image[height - 1][width - 1].rgbtBlue = round((originalImage[height - 1][width - 1].rgbtBlue + originalImage[height - 2][width - 1].rgbtBlue + originalImage[height - 1][width - 2].rgbtBlue + originalImage[height - 2][width - 2].rgbtBlue) / 4.);
        image[0][0].rgbtGreen = round((originalImage[0][0].rgbtGreen + originalImage[0][1].rgbtGreen + originalImage[1][0].rgbtGreen + originalImage[1][1].rgbtGreen) / 4.);
        image[height - 1][0].rgbtGreen = round((originalImage[height - 1][0].rgbtGreen + originalImage[height - 2][0].rgbtGreen + originalImage[height - 1][1].rgbtGreen + originalImage[height - 2][1].rgbtGreen) / 4.);
        image[0][width - 1].rgbtGreen = round((originalImage[0][width - 1].rgbtGreen + originalImage[1][width - 1].rgbtGreen + originalImage[0][width - 2].rgbtGreen + originalImage[1][width - 2].rgbtGreen) / 4.);
        image[height - 1][width - 1].rgbtGreen = round((originalImage[height - 1][width - 1].rgbtGreen + originalImage[height - 2][width - 1].rgbtGreen + originalImage[height - 1][width - 2].rgbtGreen + originalImage[height - 2][width - 2].rgbtGreen) / 4.);
        image[0][0].rgbtRed = round((originalImage[0][0].rgbtRed + originalImage[0][1].rgbtRed + originalImage[1][0].rgbtRed + originalImage[1][1].rgbtRed) / 4.);
        image[height - 1][0].rgbtRed = round((originalImage[height - 1][0].rgbtRed + originalImage[height - 2][0].rgbtRed + originalImage[height - 1][1].rgbtRed + originalImage[height - 2][1].rgbtRed) / 4.);
        image[0][width - 1].rgbtRed = round((originalImage[0][width - 1].rgbtRed + originalImage[1][width - 1].rgbtRed + originalImage[0][width - 2].rgbtRed + originalImage[1][width - 2].rgbtRed) / 4.);
        image[height - 1][width - 1].rgbtRed = round((originalImage[height - 1][width - 1].rgbtRed + originalImage[height - 2][width - 1].rgbtRed + originalImage[height - 1][width - 2].rgbtRed + originalImage[height - 2][width - 2].rgbtRed) / 4.);
    }

    for (int i = 0; i < height; ++i) {
        free(originalImage[i]);
    }
    free(originalImage);
}

