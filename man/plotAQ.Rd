\name{plotAQ}
\alias{plotAQ}
\title{plot A/Q curve}
\usage{
plotAQ(data, fittd, id.col = 1, trt.col = 2, ylab = "CO2 Uptake",
  xlab = "Quantum flux", by = c("trt", "ID"), type = "o", ...)
}
\arguments{
  \item{data}{is assumed to have the following structure
  col 1: trt col 2 (optional): other treatment factor col
  2: Assimilation col 3: Quantum flux col 4: Temperature
  col 5: Relative humidity col 6 (optional): Reference CO2}

  \item{fittd}{}

  \item{id.col}{}

  \item{trt.col}{}

  \item{ylab}{}

  \item{xlab}{}

  \item{by}{}

  \item{type}{}

  \item{...}{}
}
\value{
NULL, creates plot
}
\description{
Function to plot A/Q curves
}
\author{
Fernando E. Miguez
}

