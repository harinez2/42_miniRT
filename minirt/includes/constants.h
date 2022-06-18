/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 17:41:08 by yonishi           #+#    #+#             */
/*   Updated: 2022/06/18 17:41:08 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# define PI				3.14159265359
# define EPSILON		0.01

# define MAX_OBJ_COUNT		200
# define MAX_CAMERA_COUNT	30
# define MAX_LIGHT_COUNT	30

// for bmp file
# define FILE_HEADER_SIZE		14
# define INFO_HEADER_SIZE		40
# define DEFAULT_HEADER_SIZE	54	// FILE_HEADER_SIZE + INFO_HEADER_SIZE

# define SUCCESS			0
# define FAIL				-1

#endif
