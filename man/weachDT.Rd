\name{weachDT}
\alias{weachDT}
\title{weachDT}
\usage{
weachDT(X, lati)
}
\arguments{
  \item{X}{data table with climate variables}

  \item{lati}{latitude (for calculating solar radiation)}
}
\value{
weather file for input to BioGro and related crop growth
functions
}
\description{
Simple, Fast Daily to Hourly Climate Downscaling
}
\details{
Based on weach family of functions but 5x faster than
weachNEW, and requiring metric units (temperature in
celsius, windspeed in kph, precip in mm, relative humidity
as fraction)
}
\author{
David LeBauer
}

